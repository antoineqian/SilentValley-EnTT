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

#pragma once

#include <cstddef>
#include <algorithm>
#include <random>
#include <memory>
#include <string>
#include <deque>
#include <map>
#include <SFML/Audio.hpp>

class Jukebox
{
public:
    // Create a Jukebox containing all supported files in the given
    // directory. It will attempt to add all files in the directory
    // using sf::Music::loadFromFile(), so for best performance make
    // sure the directory does not contain any non-music files.
    explicit Jukebox(const std::string &dir);

    // Start (or resume) playing current song in the playlist.
    void play();

    // Returns true if the Jukebox is currently playing, otherwise
    // returns false.
    bool playing() const;

    // Stop playing. If play() is called later then the current song
    // in the queue will play, just as if skip(0) had been called.
    void stop();

    // Returns true if the Jukebox is currently stopped, otherwise
    // returns false.
    bool stopped() const;

    // Skips forward or backwards 'n' songs to the start of that n'th
    // song. If the playlist is not looping then skipping backwards by
    // more than the available prior songs will skip to the first song
    // and skipping forward more than the available songs will stop
    // playback as if the last song had just played.
    // Skipping forward 0 songs has the effect of skipping to the
    // start of the current song.
    // If the Jukebox was playing at the time of the skip it will
    // start playing the skipped-to song at once. If it was paused or
    // stopped it will be stopped at the start of the skipped-to song
    // when this function returns.
    void skip(int n);

    // Rewinds the playlist to the start of the first song.
    void rewind();

    // Stops playback of the current song. Calling play() after this
    // will resume the current song where it was paused.
    void pause();

    // Returns true if the Jukebox is currently paused, otherwise
    // returns false.
    bool paused() const;

    // Empty the playlist. This also stops any playback.
    void clear();

    // Add song (by filename) to end of playlist. Songs will play in
    // requested order (unless shuffle is later called). A song can be
    // added to the queue as many times as needed.
    void request(const std::string &song);

    // Add all songs in the catalog to the playlist once (in
    // order of sorted song name).
    void requestAll();

    // Shuffle all songs in the playlist. If a song is currently
    // playing (or paused) it will continue playing and be moved to
    // the head of the list.
    void shuffle();

    // Shuffle the remaining songs in the playlist. Any songs that
    // have already played are not shuffled and will play again in the
    // same order if the playlist is rewound.
    void shuffleRemaining();

    // If 'loop' is 'true' then the playlist will start again at the
    // first song once the last is done playing. Otherwise playback
    // will stop after the last song.
    // By default looping is enabled.
    void setLooping(bool loop);

    // Returns whether the playlist is currently in looping mode.
    bool looping() const;

    // Returns the total number of songs available in this Jukebox's
    // catalog.
    std::size_t songsAvailable() const;

    // Returns the current number of songs in the playlist.
    std::size_t songsInPlaylist() const;

    // Returns the number of songs remaining in the playlist including
    // the one currently playing or queued to be played.
    std::size_t songsRemaining() const;

    // Returns the filenames of the songs in this Jukebox's catalog.
    std::vector<std::string> catalog() const;

    // Returns the filenames of the songs currently in this Jukebox's
    // playlist.
    std::vector<std::string> playlist() const;

    // Returns the filename of the current song if any. Returns the
    // empty string if the playlist is empty.
    std::string current() const;

    // Set the playback volume. The volume is a value between 0 (mute)
    // and 100 (full volume). The default value for the volume is
    // 100. Values outside the valid range will be clamped to remain
    // in range.
    void setVolume(float volume);

    // Returns the current volume in the range [0-100].
    float volume() const;

    // Returns Whether the Jukebox is currently Playing, Stopped or
    // Paused.
    sf::SoundSource::Status status() const;

    // You MUST call this regularly (for example; as part of the game
    // loop) for the Jukebox to detect the end of a song and correctly
    // continue through the playlist.
    void update();

private:
    template <typename ITER>
    void shuffle_range(ITER first, ITER last)
    {
        std::random_device rd;
        auto g = std::mt19937(rd());
        std::shuffle(first, last, g);
    }

    std::map<std::string, std::unique_ptr<sf::Music>> m_catalog;
    std::deque<std::pair<std::string, sf::Music *>> m_playlist;
    sf::SoundSource::Status m_status = sf::SoundSource::Stopped;
    float m_volume = 100.f;
    std::size_t m_current = 0;
    bool m_looping = true;
};
