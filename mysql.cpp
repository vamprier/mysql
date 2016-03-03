////////////////////////////////////////////////////////////
//�� �� ����mysql.cpp
//��    �ߣ��Ծ�
//��    �ڣ�2016-01-05
//�ļ�˵��������mysql���ݿ⣬�������
////////////////////////////////////////////////////////////
#include "mysql.h"

string readData(	const string& hostName,
					const string& dbName,
					const string& userName,
					const string& password,
					const int& port,
					const string& query,
					vector< vector<string> >& dataSet)
{
	MYSQL mysql;
	//����֮ǰ���ȳ�ʼ��
	mysql_init(&mysql);

	//����mysql���ݿ�
	if(!mysql_real_connect(&mysql,hostName.data(),userName.data(),password.data(),dbName.data(),port,NULL,CLIENT_MULTI_STATEMENTS))
	{
		return "error:link database error when read data";
	}
	//���ò�ѯʱ�ı���
	mysql_query(&mysql,"set names utf8");
	//���ô洢����    
	int ret = mysql_query(&mysql, query.c_str()); 
	if( ret)
	{
		mysql_close(&mysql);
		return "error:excute sql error when read data";
	}
	//��ȡ�����
    MYSQL_RES *result = mysql_store_result(&mysql);
	unsigned int i,num_fields;
	//��ȡ�ֶ���
	num_fields = mysql_num_fields(result);
	//ѭ����ӡ������
	MYSQL_ROW row;
	while( (row=mysql_fetch_row(result))!=NULL)
	{
		vector<string> temp;
		for(i=0;i<num_fields;i++)
		{
			char* ch = row[i];
			if( ch == NULL || !strcmp(ch," ") || !strcmp(ch,"(null)"))
			{
				ch = "";
			}
			string s = ch;
			temp.push_back(s);
        }
        dataSet.push_back(temp);
    }
    //�ͷŽ����
    mysql_free_result(result);
    //�ر�����
    mysql_close(&mysql);
	return "success";
}

string writeData(	const string& hostName,
					const string& dbName,
					const string& userName,
					const string& password,
					const int& port,
					const vector<string>& querySet)
{
	MYSQL mysql;
	//����֮ǰ���ȳ�ʼ��
	mysql_init(&mysql);

	//����mysql���ݿ�
	if(!mysql_real_connect(&mysql,hostName.data(),userName.data(),password.data(),dbName.data(),port,NULL,CLIENT_MULTI_STATEMENTS))
	{
		return "error:link database error when write data";
	}
	//���ò�ѯʱ�ı���
	mysql_query(&mysql,"set names utf8");
	int size = querySet.size();
	for(int i=0;i<size;i++)
	{
		int ret = mysql_query(&mysql, querySet[i].c_str());
		if( ret)
		{
			continue;
		}
	}
	//�ر�����
	mysql_close(&mysql);
	return "success";
}

string deleteData(	const string& hostName,
					const string& dbName,
					const string& userName,
					const string& password,
					const int& port,
					const string& query)
{
	MYSQL mysql;
	//����֮ǰ���ȳ�ʼ��
	mysql_init(&mysql);

	//����mysql���ݿ�
	if(!mysql_real_connect(&mysql,hostName.data(),userName.data(),password.data(),dbName.data(),port,NULL,CLIENT_MULTI_STATEMENTS))
	{
		return "error:link database error when write data";
	}
	//���ò�ѯʱ�ı���
	mysql_query(&mysql,"set names utf8");
	int ret = mysql_query(&mysql, query.c_str());
	if( ret)
	{
		return "error:excute sql error when delete data";
	}
	//�ر�����
	mysql_close(&mysql);
	return "success";
}
