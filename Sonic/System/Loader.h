#pragma once

class Data {
public:
	//�����ް����g�p�\���ǂ�����Ԃ�
	virtual bool IsAvaillable() = 0;
	virtual ~Data() {};
};

class Loader
{
public:
	Loader();
	virtual ~Loader();

	//۰��
	//@param path ̧�ق��߽
	//@param data �ް���޼ު�Ăւ̎Q��
	virtual bool Load(const char* path, Data& data) = 0;

	//�ް��̱�۰��
	//@attention ����Ŏw�肳�ꂽ�߽�ɑΉ������ް���
	//��؏ォ�������̂ōēx�g�p����ۂͽ�ڰ�ޱ������������܂��B
	virtual void Unload(const char* path) = 0;
};

