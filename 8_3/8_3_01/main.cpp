#include<iostream>
#include<fstream>

class LogCommand {
public:
	virtual ~LogCommand() = default;
	virtual void print(const std::string& message) = 0;
};

// Ћогирование в файл
class LogFile : public LogCommand {
	std::ofstream fout;
public:
	explicit LogFile(const std::string& path) {
		fout.open(path + "out.txt");
		if (!fout.is_open()) {
			std::cout << "File opening error!\n";
		}
	}

	void print(const std::string& message) {
		fout << message << "\n";
	}
	
	~LogFile() {
		fout.close();
	}
};

// Ћогирование в консоль
class LogConsole : public LogCommand {
public:
	explicit LogConsole() {}

	void print(const std::string& message) {
		std::cout << message << std::endl;
	}
};

void print(LogCommand& log, std::string message) {
	log.print(message);
}

int main() {
	LogConsole logC;
	LogFile logF("C:\\TEMP\\");

	print(logC, "Print console!");
	print(logF, "Print file!");

	return 0;
}