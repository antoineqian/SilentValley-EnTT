// emacs: -*- Mode: c++; c-file-style: "stroustrup"; c-basic-offset: 4; indent-tabs-mode: nil; -*-
//
// This file is Copyright (C) 2014 by Jesper Juhl <jesperjuhl76@gmail.com>
// This file may be freely used under the terms of the zlib license (http://opensource.org/licenses/Zlib)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
//    1. The origin of this software must not be misrepresented; you must not claim that you wrote
//       the original software. If you use this software in a product, an acknowledgment in the
//       product documentation would be appreciated but is not required.
//
//    2. Altered source versions must be plainly marked as such, and must not be misrepresented as
//       being the original software.
//
//    3. This notice may not be removed or altered from any source distribution.

#include "Jukebox.hh"
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <cstdlib>

extern "C" typedef int (*DIRDel)(DIR *);

Jukebox::Jukebox(const std::string &dir)
{
    auto dp = std::unique_ptr<DIR, DIRDel>(opendir(dir.c_str()), closedir);
    if (!dp)
    {
        std::cerr << "Jukebox was unable to open catalog dir '"
                  << dir << "': " << strerror(errno)
                  << ": Jukebox will be empty" << std::endl;
        return;
    }

    while (const auto *de = readdir(dp.get()))
    {
        auto filename = std::string(de->d_name);
        if (filename == "." || filename == "..")
        {
            continue;
        }
        auto path = dir + "/" + filename;
        auto music = std::unique_ptr<sf::Music>(new sf::Music);
        if (!music->openFromFile(path))
        {
            std::cerr << "Jukebox failed to add '" << path << "'" << std::endl;
            continue;
        }
        const auto inserted = m_catalog.emplace(filename, std::move(music));
        assert(inserted.second);
    }
}

void Jukebox::play()
{
    if (m_playlist.empty())
    {
        assert(m_status == sf::SoundSource::Stopped);
        return;
    }

    assert(m_current >= 0);
    assert(m_current < m_playlist.size());

    setVolume(m_volume);
    m_playlist[m_current].second->play();
    m_status = sf::SoundSource::Playing;
}

bool Jukebox::playing() const
{
    return m_status == sf::SoundSource::Playing;
}

void Jukebox::stop()
{
    if (m_playlist.empty() || m_status == sf::SoundSource::Stopped)
    {
        return;
    }

    assert(m_current >= 0);
    assert(m_current < m_playlist.size());
    m_playlist[m_current].second->stop();
    m_status = sf::SoundSource::Stopped;
}

bool Jukebox::stopped() const
{
    return m_status == sf::SoundSource::Stopped;
}

void Jukebox::skip(int n)
{
    if (m_playlist.empty())
    {
        return;
    }

    assert(m_current >= 0);
    assert(m_current < m_playlist.size());

    const bool was_playing = playing();
    stop();

    if (m_looping)
    {
        if (n > 0)
        {
            m_current = (m_current + n) % m_playlist.size();
        }
        else
        {
            m_current = m_playlist.size() + ((m_current + n) % m_playlist.size());
        }
    }
    else
    {
        if (n > 0)
        {
            if (m_current + n >= m_playlist.size())
            {
                m_current = m_playlist.size() - 1;
            }
            else
            {
                m_current += n;
            }
        }
        else
        {
            if (m_current < static_cast<std::size_t>(std::labs(n)))
            {
                m_current = 0;
            }
            else
            {
                m_current += n;
            }
        }
    }
    if (was_playing)
    {
        play();
    }
}

void Jukebox::rewind()
{
    auto orig_status = m_status;
    stop();
    m_current = 0;
    if (orig_status == sf::SoundSource::Playing)
    {
        play();
    }
}

void Jukebox::pause()
{
    if (m_playlist.empty() || m_status != sf::SoundSource::Playing)
    {
        return;
    }

    assert(m_current >= 0);
    assert(m_current < m_playlist.size());
    m_playlist[m_current].second->pause();
    m_status = sf::SoundSource::Paused;
}

bool Jukebox::paused() const
{
    return m_status == sf::SoundSource::Paused;
}

void Jukebox::clear()
{
    stop();
    m_playlist.clear();
    m_current = 0;
}

void Jukebox::request(const std::string &song)
{
    auto found = m_catalog.find(song);
    if (found == m_catalog.end())
    {
        std::cerr << "Jukebox request for song '" << song
                  << "' which is not in the catalog." << std::endl;
        return;
    }
    m_playlist.emplace_back(found->first, found->second.get());
}

void Jukebox::requestAll()
{
    for (const auto &song : m_catalog)
    {
        m_playlist.emplace_back(song.first, song.second.get());
    }
}

void Jukebox::shuffle()
{
    if (m_playlist.empty())
    {
        return;
    }

    assert(m_current >= 0);
    assert(m_current < m_playlist.size());

    auto current = m_playlist[m_current];
    if (m_status != sf::SoundSource::Stopped)
    {
        auto it = begin(m_playlist);
        std::advance(it, m_current);
        m_playlist.erase(it);
    }

    shuffle_range(begin(m_playlist), end(m_playlist));

    if (m_status != sf::SoundSource::Stopped)
    {
        m_playlist.emplace_front(current);
    }

    m_current = 0;
}

void Jukebox::shuffleRemaining()
{
    if (m_playlist.empty() || m_current == m_playlist.size() - 1)
    {
        return;
    }

    assert(m_current >= 0);
    assert(m_current < m_playlist.size());

    auto first = begin(m_playlist);
    if (m_status == sf::SoundSource::Stopped)
    {
        std::advance(first, m_current);
    }
    else
    {
        std::advance(first, m_current + 1);
    }

    shuffle_range(first, end(m_playlist));
}

void Jukebox::setLooping(const bool loop)
{
    m_looping = loop;
}

bool Jukebox::looping() const
{
    return m_looping;
}

std::size_t Jukebox::songsAvailable() const
{
    return m_catalog.size();
}

std::size_t Jukebox::songsInPlaylist() const
{
    return m_playlist.size();
}

std::size_t Jukebox::songsRemaining() const
{
    return m_playlist.size() - m_current;
}

std::vector<std::string> Jukebox::catalog() const
{
    std::vector<std::string> retval;
    for (const auto &song : m_catalog)
    {
        retval.emplace_back(song.first);
    }
    return retval;
}

std::vector<std::string> Jukebox::playlist() const
{
    std::vector<std::string> retval;
    for (const auto &song : m_playlist)
    {
        retval.emplace_back(song.first);
    }
    return retval;
}

std::string Jukebox::current() const
{
    if (m_playlist.empty())
    {
        return "";
    }
    assert(m_current >= 0);
    assert(m_current < m_playlist.size());
    return m_playlist[m_current].first;
}

void Jukebox::setVolume(const float volume)
{
    m_volume = volume;
    if (m_volume < 0.f)
    {
        m_volume = 0.f;
    }
    else if (m_volume > 100.f)
    {
        m_volume = 100.f;
    }
    if (m_playlist.empty())
    {
        return;
    }
    assert(m_current >= 0);
    assert(m_current < m_playlist.size());
    m_playlist[m_current].second->setVolume(m_volume);
}

float Jukebox::volume() const
{
    return m_volume;
}

sf::SoundSource::Status Jukebox::status() const
{
    return m_status;
}

void Jukebox::update()
{
    if (m_playlist.empty())
    {
        return;
    }

    assert(m_current >= 0);
    assert(m_current < m_playlist.size());

    if (m_status == sf::SoundSource::Playing && m_playlist[m_current].second->getStatus() == sf::SoundSource::Stopped)
    {
        // The jukebox should be playing but the current music is
        // stopped. This must mean that the current song is finished
        // and we should advance to the next.

        // Reset the current song's offset to start.
        m_playlist[m_current].second->setPlayingOffset(sf::Time::Zero);

        if (m_current == m_playlist.size() - 1)
        {
            // At last song.
            if (m_looping)
            {
                // back to the first.
                m_current = 0;
                play();
            }
            else
            {
                // not looping, so we should stop playing now.
                stop();
            }
        }
        else
        {
            // not at last song, just increment to the next and start
            // playback.
            ++m_current;
            play();
        }
    }
}