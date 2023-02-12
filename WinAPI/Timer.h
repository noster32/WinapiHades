#pragma once

#pragma region Ÿ�̸�
/*
	�� Ÿ�̸�

	 - ������ ����� API ���� �Լ� (���� �����δ� ȿ���� ���� ����)
	  �� GetTickCount();
	  �� GetTickCount64();

	 - �ð��� �����ϴ� �Լ����� �⺻������ �����찡 ���۵� ���� ���� �ð��� �и� ������ ������ ��ȯ�Ѵ�.
	 - �и� �����庸�� �� �� ������ Ÿ�̸Ӹ� ���Ѵٸ� ���� Ÿ�̸Ӹ� �����ؾ� �Ѵ�.
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

		 �� ���� Ÿ�̸��� ��� ��ø�� ��Ű�� ��ø�� ��Ų ��ŭ ȿ���� �ö󰣴�. �ڡڡڡڡڡڡڡڡڡ�
		  �� �ٸ�, ���� ���ƾ� �� ���� ����. �������� �ڵ带 ¥�� �ϵ���� �ε����� ������ �ø���.
		  �� Ÿ�̸Ӵ� CPU�� �������� �����ϱ⿡ CPU�� ���� �ε����� ����, GPU�� ���� ������ �߻�.


	 - 
*/
#pragma endregion

class Timer
{
public:
	Timer();
	~Timer();

	void start();
	void stop();
	double getElapsedTime();
	double getElapsedTimeInSec();
	double getElapsedTimeInMilliSec();
	double getElapsedTimeInMicroSec();


private:
	double startTimeInMicroSec;
	double endTimeInMicroSec;
	int stopped;

	LARGE_INTEGER frequency;
	LARGE_INTEGER startCount;
	LARGE_INTEGER endCount;
};