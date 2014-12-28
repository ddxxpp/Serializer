
#include "serializer.h"

#define CHECK_SIZE(length)\
if (m_begin + length > m_end)\
	{\
	return false; \
	}\


bool Serializer::Push(const char * const data, unsigned int length)
{
	CHECK_SIZE(length);
	memcpy(m_data + m_begin, data, length);
	m_begin += length;
	return true;
}

bool Serializer::Pop(char *data, unsigned int length)
{
	CHECK_SIZE(length);
	memcpy(data, m_data + m_begin, length);
	m_begin += length;
	return true;
}

bool Serializer::PushStr(const char * const data, unsigned int length)
{
	CHECK_SIZE(LEN_INT);
	*(unsigned int *)(m_data + m_begin) = length;
	m_begin += LEN_INT;

	CHECK_SIZE(length);
	memcpy(m_data + m_begin, data, length);
	m_begin += length;
	return true;
}

bool Serializer::PopStr(char **data, unsigned int &length)
{
	CHECK_SIZE(LEN_INT);
	length = *(unsigned int *)(m_data + m_begin);
	m_begin += LEN_INT;

	CHECK_SIZE(length);
	*data = m_data + m_begin;
	m_begin += length;
	return true;
}

