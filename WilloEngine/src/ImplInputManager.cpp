#include "ImplInputManager.hpp"

#include <iostream>

#include <WilloEngine/Profiling.hpp>

namespace WilloEngine
{
    bool InputManager::Create(InputManager& inputManager, bool use_GetKey)
    {
        inputManager.impl = std::make_shared<ImplInputManager>();
        if (!inputManager.impl->Init(use_GetKey)) {
            inputManager.impl.reset();
            return false;
        }
        return true;
    }

    bool ImplInputManager::Init(bool useGetKey)
    {
        _useGetKey = useGetKey;

        return true;
    }

    void InputManager::Update() { impl->Update(); }
    void ImplInputManager::Update()
    {
        WILLO_ENGINE_PROFILE_C(WilloEngine::Profiling::Colour::Aqua);

        if (_useGetKey)
            _pressKeys.clear();

        while (!_inputEventQueue.empty())
        {
            std::pair<KEY_CODE,INPUT_EVENT_TYPE> pair = _inputEventQueue.front();
            _inputEventQueue.pop();

            RunCallbacks(pair.first, pair.second);

            if (!_useGetKey)
                return;

            if (pair.second == INPUT_EVENT_TYPE::KEY_PRESSED) {
                _pressKeys.insert(std::pair(pair.first, true));
            } else if (pair.second == INPUT_EVENT_TYPE::KEY_RELEASED) {
                _releaseKeys.insert(std::pair(pair.first, true));
            }
        }
    }

    void ImplInputManager::RunCallbacks(KEY_CODE keyCode, INPUT_EVENT_TYPE eventType)
    {
        WILLO_ENGINE_PROFILE_C(WilloEngine::Profiling::Colour::Aqua);
        // key press
        if (eventType == INPUT_EVENT_TYPE::KEY_PRESSED) {
            auto pressCallbacks = _keycodePressCallbacks.find(keyCode);
            if (pressCallbacks != _keycodePressCallbacks.end()) {
                size_t numCallbacks = pressCallbacks->second.size();
                for (size_t i = 0; i < numCallbacks; i++) {
                    pressCallbacks->second.at(i)();
                }
            }

            size_t numCallbacks = _eventPressCallbacks.size();
            for (size_t i = 0; i < numCallbacks; i++) {
                _eventPressCallbacks.at(i)(keyCode);
            }
        }

        // key release
        if (eventType == INPUT_EVENT_TYPE::KEY_RELEASED) {
            auto releaseCallbacks = _keycodeReleaseCallbacks.find(keyCode);
            if (releaseCallbacks != _keycodeReleaseCallbacks.end()) {
                size_t numCallbacks = releaseCallbacks->second.size();
                for (size_t i = 0; i < numCallbacks; i++) {
                    releaseCallbacks->second.at(i)();
                }
            }

            size_t numCallbacks = _eventReleaseCallbacks.size();
            for (size_t i = 0; i < numCallbacks; i++) {
                _eventReleaseCallbacks.at(i)(keyCode);
            }
        }
    }

    void InputManager::ReceiveKeypressEvent(KEY_CODE keyCode, INPUT_EVENT_TYPE eventType) { impl->ReceiveKeypressEvent(keyCode, eventType); }
    void ImplInputManager::ReceiveKeypressEvent(KEY_CODE keyCode, INPUT_EVENT_TYPE eventType)
    {
        WILLO_ENGINE_PROFILE_C(WilloEngine::Profiling::Colour::Aqua);
        _inputEventQueue.push(std::pair(keyCode, eventType));
    }

    bool InputManager::GetKey(KEY_CODE keyCode, INPUT_EVENT_TYPE eventType) { return impl->GetKey(keyCode, eventType); }
    bool ImplInputManager::GetKey(KEY_CODE keyCode, INPUT_EVENT_TYPE eventType)
    {
        WILLO_ENGINE_PROFILE_C(WilloEngine::Profiling::Colour::Aqua);
        if (eventType == INPUT_EVENT_TYPE::KEY_PRESSED)
        {
            auto iter = _pressKeys.find(keyCode);
            if (iter != _pressKeys.end()) {
                return iter->second;
            } else {
                return false;
            }
        }
        else
        {
            auto iter = _releaseKeys.find(keyCode);
            if (iter != _releaseKeys.end()) {
                return iter->second;
            } else {
                return false;
            }
        }
    }

    void InputManager::SubscribeKey(KEY_CODE keyCode, INPUT_EVENT_TYPE eventType, std::function<void()> callback) {
        impl->SubscribeKey(keyCode, eventType, callback); }
    void ImplInputManager::SubscribeKey(KEY_CODE keyCode, INPUT_EVENT_TYPE eventType, std::function<void()> callback)
    {
        WILLO_ENGINE_PROFILE_C(WilloEngine::Profiling::Colour::Aqua);
        if (eventType == INPUT_EVENT_TYPE::KEY_PRESSED) {
            if (_keycodePressCallbacks.find(keyCode) == _keycodePressCallbacks.end()) {
                _keycodePressCallbacks.insert(std::pair(keyCode, std::vector<std::function<void()>>()));
            }
            _keycodePressCallbacks.at(keyCode).push_back(callback);
        } else {
            if (_keycodeReleaseCallbacks.find(keyCode) == _keycodeReleaseCallbacks.end()) {
                _keycodeReleaseCallbacks.insert(std::pair(keyCode, std::vector<std::function<void()>>()));
            }
            _keycodeReleaseCallbacks.at(keyCode).push_back(callback);
        }
    }

    void InputManager::SubscribeKey(INPUT_EVENT_TYPE eventType, std::function<void(KEY_CODE)> callback) {
        impl->SubscribeKey(eventType, callback); }
    void ImplInputManager::SubscribeKey(INPUT_EVENT_TYPE eventType, std::function<void(KEY_CODE)> callback)
    {
        WILLO_ENGINE_PROFILE_C(WilloEngine::Profiling::Colour::Aqua);
        if (eventType == INPUT_EVENT_TYPE::KEY_PRESSED) {
            _eventPressCallbacks.push_back(callback);
        } else {
            _eventReleaseCallbacks.push_back(callback);
        }
    }
}
