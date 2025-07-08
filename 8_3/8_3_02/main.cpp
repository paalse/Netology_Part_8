#include <fstream>
#include <iostream>
#include <vector>

// Интерфейс для классов наблюдателей
class Observer {
public:
	virtual void onWarning(const std::string& message) {}
	virtual void onError(const std::string& message) {}
	virtual void onFatalError(const std::string& message) {}
};

class WarningMsg : public Observer {
public:
	void onWarning(const std::string& message) override {
		std::cout << message << std::endl;
	}
};

// Класс для работы с ошибками Error, выводит сообщение в консоль и файл
class ErrorMsg : public Observer {
private:
	std::ofstream logFile;
	std::string filenameWithPath;
public:
	ErrorMsg(const std::string& path) {
		filenameWithPath = path + "ErrorLog.txt";
		logFile.open(filenameWithPath);
		if (!(logFile.is_open())) {
			std::cout << "File " << path + "ErrorLog.txt" << " not found." << std::endl;
		}
	}

	~ErrorMsg() {
		logFile.close();
	}

	void onError(const std::string& message) override {
		logFile << message << std::endl;
		std::cout << message << " success writen in file " << filenameWithPath << std::endl;
	}
};

// Класс для работы с ошибками Fatal, выводит сообщение в консоль и файл
class FatalErrorMsg : public Observer {
private:
	std::ofstream logFile;
	std::string filenameWithPath;
public:
	FatalErrorMsg(const std::string& path) {
		filenameWithPath = path + "FatalErrorLog.txt";
		logFile.open(filenameWithPath);
		if (!(logFile.is_open())) {
			std::cout << "File " << filenameWithPath << " not found." << std::endl;
		}
	}

	~FatalErrorMsg() {
		logFile.close();
	}

	void onFatalError(const std::string& message) override {
		std::cout << message << std::endl;
		logFile << message << std::endl;
		std::cout << message << " success writen in file " << filenameWithPath << std::endl;
	}
};

//Наблюдаемый класс 
class Observered {
private:
	std::vector<std::weak_ptr<Observer>> vObservers;
public:
	// Добавление класса наблюдателя в список оповещения
	void addObserver(std::weak_ptr<Observer> observer) {
		vObservers.push_back(observer);
	}

	// Оповещение классов наблюдателей о Warning
	void warning(const std::string& message) const {
		for (auto& obs : vObservers) {
			if (auto strong_ptr = obs.lock()) {
				strong_ptr->onWarning(message);
			}
		}
	}

	// Оповещение классов наблюдателей о Error
	void error(const std::string& message) const {
		for (auto& obs : vObservers) {
			if (auto strong_ptr = obs.lock()) {
				strong_ptr->onError(message);
			}
		}
	}

	// Оповещение классов наблюдателей о Fatal
	void fatalError(const std::string& message) const {
		for (auto& obs : vObservers) {
			if (auto strong_ptr = obs.lock()) {
				strong_ptr->onFatalError(message);
			}
		}
	}
};

int main() {
	auto warning = std::make_shared<WarningMsg>();
	auto error = std::make_shared<ErrorMsg>("C:\\TEMP\\");
	auto fatal = std::make_shared <FatalErrorMsg>("C:\\TEMP\\");

	Observered observered;

	observered.addObserver(warning);
	observered.warning("Warning message");
		
	observered.addObserver(error);
	observered.error("Error message");
		
	observered.addObserver(fatal);
	observered.fatalError("Fatal error message");

	return 0;
}

