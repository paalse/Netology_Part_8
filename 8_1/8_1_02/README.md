Задание 2
Расширьте класс из предыдущего задания методом

SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept;
С помощью которого можно будет добавить в запрос сразу несколько условий.

Расширьте класс из предыдущего задания методом

SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept;
С помощью этого метода можно добавить в запрос сразу несколько полей, по которым он будет строиться вместо одного, как в базовом варианте.