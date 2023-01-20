#pragma once

#pragma region Ÿ�̸�
/*
	�� Ÿ�̸�

	 - ������ ����� API ���� �Լ� (���� �����δ� ȿ���� ���� ����)
	  �� GetTickCount();
	  �� GetTickCount64();

	 - �ð��� �����ϴ� �Լ����� �⺻������ �����찡 ���۵� ���� ���� �ð��� �и� ������ ������ ��ȯ�Ѵ�.
	 - �и� �����庸�� �� �� ������ Ÿ�̸Ӹ� ���Ѵٸ� ������ Ÿ�̸Ӹ� �����ؾ� �Ѵ�.
	 - ���� Ÿ�̸Ӹ� ������ ���� �� ������ �������.
	 �ڡڡڡڡ�
	  �� 1. �ػ�
	  �� 2. Ŭ�� (���� ��)

	   �� �ػ󵵶�?
	    - �پ��� �ð� �Լ����� �ð��� �����ϱ� ���� Tick ��� ������ �ִ�.
		 �� ���� 1���� �������� �󸶳� ���� ���������� ���� �� �ִ��� ���.
		- 1�� ���� �󸶳� ���� Tick���� ������ �ð��� ��Ȯ���� ���̴��İ�
		���ػ󵵿� ���ػ��� ���������� �Ǵ� ����.

	   �� Clock
	    - Ÿ�̸ӿ��� ����ϴ� Ŭ���� ���� CPU Clock�� �ǹ��Ѵ�.
		
		- Ŭ���̶�?
		 �� Ŭ���� ������ ȸ���� ������ ���� ���̸� Hz ������ ǥ��.
		 �� ex) 1�ʿ� 1Hz�� ��ȣ�� �� �� �ش�. (0 �Ǵ� 1). 
		 �� 1Ghz�� 10�� 9���� -> 1�ʿ� 10�� �� ��Ʈ�� �ű��.

	    - Ÿ�̸� ����
		 �� Milli Second
		 �� 10 Milli Second
		 �� 100 Milli Second

		 �� ������ Ÿ�̸��� ��� ��ø�� ��Ű�� ��ø�� ��Ų ��ŭ ȿ���� �ö󰣴�. �ڡڡڡڡڡڡڡڡڡ�
		  �� �ٸ�, ���� ���ƾ� �� ���� ����. �������� �ڵ带 ¥�� �ϵ���� �ε����� ������ �ø���.
		  �� Ÿ�̸Ӵ� CPU�� �������� �����ϱ⿡ CPU�� ���� �ε����� ����, GPU�� ���� ������ �߻�.


	 - 
*/
#pragma endregion

class Timer
{
private:
	float			_timeScale;			//����ð� ����
	float			_timeElapsed;		//������ �ð��� ����ð��� �����
	bool			_isHardware;		//������ Ÿ�̸� ���� ����
	
	//__ : �õ��ڵ忡�� ������ ������ ���Խ��� �ƴϴ�
	/*
	- int vs long
	�� 32��Ʈ vs 64��Ʈ -> 32bit ȯ�濡���� �Ѵ� 4����Ʈ : 21��
					   -> 64bit ȯ�濡���� long�� 8����Ʈ�� ġȯ��

	- __int64 vs long
	�� __int64 �� 32bit ȯ�濡���� 64bit �� �۵�������
	long�� 32bit ȯ�濡���� 32bit �� �۵��ȴ�.
	*/
	__int64			_curTime;			//���� �ð�
	__int64			_lastTime;			//���� �ð�
	__int64			_periodFrequency;	//�ð� �ֱ�

	unsigned long	_frameRate;			//FPS (�ʴ� ������ ��)
	unsigned long	_FPSFrameCount;		//FPS ī��Ʈ
	float			_FPSTimeElapsed;	//FPS �ð� �����
	float			_worldTime;			//������ ���۵� �� ����� ��ü �ð�

public:
	HRESULT init(void);
	void tick(float lockFPS = 0.0f);	//�𸮾����� ����߱� ������ update ��� tick ���

	//const �� �Լ� �� Ȥ�� ���ڿ� ������ ���������
	//const�� �Լ��� �ڿ� ������ ��� �Լ��� ���ȭ�� �ǹ��Ѵ�.
	//�� �� �Լ������� ��� ������ �� ������ ���´�. -> ���������� ����ؾ��ϱ⶧���� ���� ����Ǹ� �ȵ�
	//�� ��������� ����� �� �ִ� ��ȸ�� ���� ������ ���� ���� ���� �Ұ�
	//�� ������ x
	//���� FPS
	unsigned long getFrameRate(char* str = nullptr) const;
	//������ �ð��� ���� �ð��� �����
	inline float getElapsedTime(void) const { return _timeElapsed; }
	//��ü ��� �ð�
	inline float getWorldTime(void) const { return _worldTime; }

	/*
	update() �� �ھ� Ŭ���������� ���� ����ϸ� �ȵȴ�.
	�� ����. �������� ������� �� ����. (60���� ������ ��������� ������� ���� �߻�)
		�� update()�� �ϵ������ ������ ������ ���� �޴´� -> �ʴ� 60�� ȣ���� ������� �� ����.
		=> �������� �ٽ� �����Ű�� �ð��� �������Ѽ� �����ϰ� �̾Ƴ� �� �ְ� ������ �Ѵ�.
	*/



	Timer() {}
	~Timer() {}
};