
#ifndef TEST_SERIALIZER_H
#define TEST_SERIALIZER_H

#include <vector>
#include "serializer.h"

namespace TestSerializer
{
	class TestData
	{
	public:
		TestData(){};
		~TestData(){};

		bool		Serialize(Serializer &stream) const;
		bool		Unserialize(Serializer &stream);

		struct DataStruct
		{
			int a;
			short b;
			char c;
			char d;
			long long e;
			float f;
			double g;
		};


		DataStruct m_data_struct;
		typedef std::vector<int> VECTOR_TEST;
		typedef std::vector<std::string> VECTOR_NAME;

		VECTOR_TEST role_data;
		VECTOR_NAME role_name;
	};

	bool TestData::Serialize(Serializer &stream) const
	{
		stream.Push(m_data_struct);
		stream.Push(role_data.size());
		for (VECTOR_TEST::const_iterator itr = role_data.begin(); itr != role_data.end(); ++itr)
		{
			stream.Push((*itr));
		}

		stream.Push(role_name.size());
		for (VECTOR_NAME::const_iterator itr = role_name.begin(); itr != role_name.end(); ++itr)
		{
			stream.PushStr(itr->c_str(), itr->length() + 1);
		}
		return true;
	}

	bool TestData::Unserialize(Serializer &stream)
	{
		stream.Pop(m_data_struct);
		unsigned int size = 0;
		stream.Pop(size);
		int data = 0;
		for (unsigned int i = 0; i < size; ++i)
		{
			stream.Pop(data);
			role_data.push_back(data);
		}

		stream.Pop(size);
		char *str = 0;
		unsigned int length = 0;
		bool ret = false;
		for (unsigned int i = 0; i < size; ++i)
		{
			ret = stream.PopStr(&str, length);
			if (!ret)
			{
				return ret;
			}
			role_name.push_back(str);
		}
		return true;
	}

	void Normal()
	{
		TestData src_data;
		TestData des_data;

		src_data.m_data_struct.a = 11;
		src_data.m_data_struct.b = 22;
		src_data.m_data_struct.c = 33;
		src_data.m_data_struct.d = 44;
		src_data.m_data_struct.e = 55;
		src_data.m_data_struct.f = (float)66.6;
		src_data.m_data_struct.g = -77.7;

		src_data.role_data.push_back(88);
		src_data.role_data.push_back(99);

		src_data.role_name.push_back("xian");
		src_data.role_name.push_back("jia");
		src_data.role_name.push_back("ming");

		// src_data and des_data will be the same
		char data[1024] = { 0 };
		Serializer temp1(data, 1024);
		src_data.Serialize(temp1);

		Serializer temp2(data, 1024);
		des_data.Unserialize(temp2);
	}
}

#endif