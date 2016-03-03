////////////////////////////////////////////////////////////
//文 件 名：mysql.cpp
//作    者：赵娟
//日    期：2016-01-05
//文件说明：连接mysql数据库，获得数据
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
	//连接之前得先初始化
	mysql_init(&mysql);

	//连接mysql数据库
	if(!mysql_real_connect(&mysql,hostName.data(),userName.data(),password.data(),dbName.data(),port,NULL,CLIENT_MULTI_STATEMENTS))
	{
		return "error:link database error when read data";
	}
	//设置查询时的编码
	mysql_query(&mysql,"set names utf8");
	//调用存储过程    
	int ret = mysql_query(&mysql, query.c_str()); 
	if( ret)
	{
		mysql_close(&mysql);
		return "error:excute sql error when read data";
	}
	//获取结果集
    MYSQL_RES *result = mysql_store_result(&mysql);
	unsigned int i,num_fields;
	//获取字段数
	num_fields = mysql_num_fields(result);
	//循环打印出各行
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
    //释放结果集
    mysql_free_result(result);
    //关闭连接
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
	//连接之前得先初始化
	mysql_init(&mysql);

	//连接mysql数据库
	if(!mysql_real_connect(&mysql,hostName.data(),userName.data(),password.data(),dbName.data(),port,NULL,CLIENT_MULTI_STATEMENTS))
	{
		return "error:link database error when write data";
	}
	//设置查询时的编码
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
	//关闭连接
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
	//连接之前得先初始化
	mysql_init(&mysql);

	//连接mysql数据库
	if(!mysql_real_connect(&mysql,hostName.data(),userName.data(),password.data(),dbName.data(),port,NULL,CLIENT_MULTI_STATEMENTS))
	{
		return "error:link database error when write data";
	}
	//设置查询时的编码
	mysql_query(&mysql,"set names utf8");
	int ret = mysql_query(&mysql, query.c_str());
	if( ret)
	{
		return "error:excute sql error when delete data";
	}
	//关闭连接
	mysql_close(&mysql);
	return "success";
}
