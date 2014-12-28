
#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <list>

#define PUSH(STREAM, VAL)\
	STREAM.Push((char *)&VAL, sizeof(VAL)); \

#define POP(STREAM, VAL)\
	STREAM.Pop((char *)&VAL, sizeof(VAL)); \


class Serializer
{
public:
	Serializer(char *data, unsigned int length)
		: m_data(data)
		, m_begin(0)
		, m_end(length)
	{

	};
	~Serializer(){};

	static const unsigned int LEN_INT = sizeof(int);

	bool	Push(const char * const data, unsigned int length);
	bool	Pop(char *data, unsigned int length);

	bool	PushStr(const char * const data, unsigned int length);
	bool	PopStr(char **data, unsigned int &length);

	template<class T>
	bool	Push(const T &data)
	{
		static unsigned int length = sizeof(T);
		if (m_begin + length > m_end)
		{
			return false;
		}
		*(T *)(m_data + m_begin) = data;
		m_begin += length;
		return true;
	}

	template<class T>
	bool	Pop(T &data)
	{
		static unsigned int length = sizeof(T);
		if (m_begin + length > m_end)
		{
			return false;
		}
		data = *(T *)(m_data + m_begin);
		m_begin += length;
		return true;
	}
private:
	char	*m_data;
	unsigned int m_begin;
	unsigned int m_end;
};

#endif