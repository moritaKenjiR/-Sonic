#include "Input.h"
#include <DxLib.h>
#include <cassert>

Input::Input()
{
	_inputTable.resize(GetJoypadNum() + 1);
	_padstate.resize(GetJoypadNum());
	_currentState.resize(GetJoypadNum()+1);
	_lastState.resize(GetJoypadNum() + 1);
}


Input::~Input()
{
}

int Input::GetConnectedPadCount(void) const
{
	return GetJoypadNum();
}

void Input::AddCommand(int plNo, std::string cmd, int periNo, int code)
{
	_inputMap.emplace(PeripheralInfo(periNo, code),  std::make_pair(plNo,cmd));
	_inputTable[plNo].emplace(cmd, PeripheralInfo(periNo, code));
}

void Input::Update(void)
{
	copy(_currentState.begin(), _currentState.end(), _lastState.begin());
	GetHitKeyStateAll(_keystate);
	for (int i = 0; i < GetJoypadNum(); ++i)
	{
		_padstate[i] = GetJoypadInputState(DX_INPUT_PAD1 + i);
	}

	for (auto &p : _currentState)
	{
		for (auto& cmd : p)
		{
			cmd.second = false;
		}
	}

	for (auto& input : _inputMap)
	{
		auto& playerNo = input.second.first;
		auto& cmd = input.second.second;
		bool ispressed = false;
		if (input.first.periNo == 0)
		{
			ispressed = ispressed || _keystate[input.first.code];
		}
		else
		{
			ispressed = ispressed || _padstate[input.first.periNo - 1] & input.first.code;
		}
		_currentState[playerNo][cmd] = _currentState[playerNo][cmd] || ispressed;
	}
}

bool Input::Ispressed(int plNo, std::string cmd) const
{
	assert(plNo < _currentState.size());
	auto& ret = _currentState[plNo];
	auto it = ret.find(cmd);
	if (it != ret.end())
	{
		return it->second;
	}
	return false;
	
/*
	auto range = _inputTable[plNo].equal_range(cmd);
	if (range.first == range.second)
	{
		return false;
	}
	bool ispressed = false;
	for (auto it = range.first; it != range.second; ++it)
	{
		if (it->second.periNo == 0)
		{
			ispressed = ispressed ||  _keystate[it->second.code];
		}
		else
		{
			ispressed = ispressed || _padstate[it->second.periNo - 1] & it->second.code;
		}
	}
	return ispressed;*/
}

bool Input::IsTriggered(int plNo, std::string cmd) const
{
	assert(plNo < _currentState.size());
	auto& cur = _currentState[plNo];
	auto& last = _lastState[plNo];
	auto it = cur.find(cmd);
	if (it != cur.end())
	{
		if (it->second) {
			auto lit = last.find(cmd);
			return lit->second;
		}
	}
	return false;
}


bool operator<(const PeripheralInfo & lval, const PeripheralInfo & rval)
{
	if (lval.periNo == rval.periNo)
	{
		return lval.code < rval.code;
	}
	return false;
}

bool operator==(const PeripheralInfo & lval, const PeripheralInfo & rval)
{
	if (lval.periNo == rval.periNo)
	{
		return lval.code == rval.code;
	}
	return false;
}

bool operator!=(const PeripheralInfo & lval, const PeripheralInfo & rval)
{
	if (lval.periNo == rval.periNo)
	{
		return lval.code != rval.code;
	}
	return false;
}
