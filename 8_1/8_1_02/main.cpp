#include <iostream>
#include "sql_query_builder.h"

int main()
{
	SqlSelectQueryBuilder query_builder;
	//  query_builder.AddColumn("name").AddColumn("phone");
	query_builder.AddColumns(std::vector<std::string> { "name", "phone" });
	query_builder.AddFrom("students");
	//query_builder.AddWhere("id", "42").AddWhere("name", "John");
	query_builder.AddWhere(std::map<std::string, std::string> { {"id", "42"}, { "name", "John" } });

	std::cout << query_builder.BuildQuery() << std::endl;
}