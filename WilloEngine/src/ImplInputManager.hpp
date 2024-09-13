#pragma once

#include "WilloEngine/InputManager.hpp"

#include <queue>
#include <unordered_map>

namespace WilloEngine
{
    struct ImplInputManager
    {
        // in theory this should be comedy levels of slow but honestly it doesn't even show up on profiling zoomed out to 6ms
        std::queue<std::pair<KEY_CODE,INPUT_EVENT_TYPE>> _inputEventQueue;

        std::unordered_map<KEY_CODE, bool> _pressKeys;
        std::unordered_map<KEY_CODE, bool> _releaseKeys;

        std::unordered_map<KEY_CODE, std::vector<std::function<void()>>> _keycodePressCallbacks;
        std::unordered_map<KEY_CODE, std::vector<std::function<void()>>> _keycodeReleaseCallbacks;

        std::vector<std::function<void(KEY_CODE)>> _eventPressCallbacks;
        std::vector<std::function<void(KEY_CODE)>> _eventReleaseCallbacks;

        bool _useGetKey = true;

        bool Init(bool useGetKey);

        void Update();
        void RunCallbacks(KEY_CODE keyCode, INPUT_EVENT_TYPE eventType);

        void ReceiveKeypressEvent(KEY_CODE keyCode, INPUT_EVENT_TYPE eventType);

        bool GetKey(KEY_CODE keyCode, INPUT_EVENT_TYPE eventType);

        void SubscribeKey(KEY_CODE keyCode, INPUT_EVENT_TYPE eventType, std::function<void()> callback);
        void SubscribeKey(INPUT_EVENT_TYPE eventType, std::function<void(KEY_CODE)> callback);
    };
}
