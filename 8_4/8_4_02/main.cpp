#include <fstream>

class Printable {
public:
	virtual ~Printable() = default;
	virtual std::string print() const = 0;
};

class DataHTML : public Printable {
	std::string data_;
public:
	DataHTML(std::string data) : data_(data) {}

	std::string print() const override {
		return "<html>" + data_ + "<html/>";
	}
};

class DataText : public Printable {
	std::string data_;
public:
	DataText(std::string data) : data_(data) {}

	std::string print() const override {
		return data_;
	}
};

class DataJSON : public Printable {
	std::string data_;
public:
	DataJSON(std::string data) : data_(data) {}

	std::string print() const override {
		return "{\"data\": \"" + data_ + "\"}";
	}
};

void saveTo(std::ofstream& file, const Printable* printable) {
	file << printable->print();
	file << std::endl;
}

int main()
{
	Printable* printableText = new DataText("Text data");
	Printable* printableHTML = new DataHTML("HTML dara");
	Printable* printableJSON = new DataJSON("JSON data");

	std::ofstream fout("out.txt");
	if (fout.is_open()) {
		saveTo(fout, printableText);
		saveTo(fout, printableHTML);
		saveTo(fout, printableJSON);
	}
	fout.close();
	return 0;
}