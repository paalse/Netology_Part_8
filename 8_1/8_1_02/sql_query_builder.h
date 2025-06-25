#pragma once
#include <iostream>
#include <vector>
#include <map>

struct Query {
	std::vector<std::string> column;
	std::string from;
	std::map<std::string, std::string> where;
};


class SqlSelectQueryBuilder {
private:
	Query query;
public:
	explicit SqlSelectQueryBuilder(){}	

	// Добавление колонки
	SqlSelectQueryBuilder& AddColumn(const std::string& column) noexcept
	{
		query.column.push_back(column);
		return *this;
	}

	// Добавление колонок
	SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept
	{
		for (auto& elem : columns) {
			query.column.push_back(elem);
		}
		return *this;
	}


	// Добавление таблицы для выборки
	SqlSelectQueryBuilder& AddFrom(const std::string& table) noexcept
	{
		query.from = table;
		return *this;
	}

	// Добавлелние условий выборки
	SqlSelectQueryBuilder& AddWhere(const std::string& key, const std::string& value) noexcept
	{
		query.where[key] = value;
		return *this;
	}

	SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept
	{
		for (auto& elem : kv) {
			query.where[elem.first] = elem.second;
		}
		return *this;
	}

	// Формирование строки запроса
	std::string BuildQuery() noexcept 
	{
		std::string result = "";

		result = "SELECT ";
		if (query.column.empty()) {
			result = result + "*";
		}
		else {
			for (int i = 0; i < query.column.size(); i++) {
				result = result + query.column[i];
				if (i != query.column.size() - 1) {
					result = result + ", ";
				}
			}
		}

		result = result + " FROM " + query.from;

		if (!query.where.empty()) {
			result = result + " WHERE ";
			int j = 0;
			for (auto elem : query.where) {
				result = result + elem.first + "=" + elem.second;
				if (j != query.where.size() - 1) {
					result = result + " AND ";
				}
				j++;
			}
		}

		result = result + ";";

		return result;
	}
};