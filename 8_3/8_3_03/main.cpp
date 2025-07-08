#include <iostream>
#include <fstream>
#include <exception>

// Типы ошибок
enum class Type {
    WARRING,    // Предупреждение
    ERROR,      // Ошибка
    FATALERROR, // Фатальная ошибка
    UNKNOWN     // Неизвестная ошибка
};

// Базовый класс для обработчиков ошибок
class LogMessage {
private:
    Type type_;             // Тип ошибки
    std::string message_;   // Сообщение об ошибке
public:
    Type type() const {
        return type_;
    };

    const std::string& message() const {
        return message_;
    };

    // Установка следующего по порядку обработчика
    virtual void SetNextHandler(std::shared_ptr<LogMessage> handler) = 0;
    // Вызов следующего обработчика 
    virtual void LogRequest(Type type, std::string const& message) = 0;
};

// Обработчик предупреждения
class WarringHandler : public LogMessage {
private:
    std::shared_ptr<LogMessage> NextHandler = nullptr;
public:
    void SetNextHandler(std::shared_ptr<LogMessage> handler) override {
        NextHandler = handler;
    }

    void LogRequest(Type type, std::string const& message) override {
        if (type == Type::WARRING) {
            std::cout << "WARRING message \"" << message << "\"\n";
        }
        else if (NextHandler != nullptr) {
            NextHandler->LogRequest(type, message);
        }
        else {
            std::cout << "Unknown message \"" << message << "\"\n";
        }
    }
};

// Обработчик ошибки
class ErrorHandler : public LogMessage {
private:
    std::shared_ptr<LogMessage>  NextHandler = nullptr;
public:
    void SetNextHandler(std::shared_ptr<LogMessage>  handler) override {
        NextHandler = handler;
    }

    void LogRequest(Type type, std::string const& message) override {
        if (type == Type::ERROR) {
            std::ofstream outputFile("error.log");

            if (outputFile.is_open()) {
                outputFile << message << std::endl;
                outputFile.close();
                std::cout << "ERROR message \"" << message << "\" was written to error.log\n";
            }
            else {
                std::cerr << "Error opening file\n";
            }
        }
        else if (NextHandler != nullptr) {
            NextHandler->LogRequest(type, message);
        }
        else {
            std::cout << "Unknown type \"" << message << "\"\n";
        }
    }
};

// Обработчик фатальной ошибки
class FatalHandler : public LogMessage {
private:
    std::shared_ptr<LogMessage>  NextHandler = nullptr;
public:
    void SetNextHandler(std::shared_ptr<LogMessage>  handler) override {
        NextHandler = handler;
    }

    void LogRequest(Type type, std::string const& message) override {
        if (type == Type::FATALERROR) {
            std::ofstream outputFile("error.log");

            if (outputFile.is_open()) {
                outputFile << message << std::endl;
                outputFile.close();
                std::cout << "FATALERROR message \"" << message << "\" was written to error.log\n";
            }
            else {
                std::cerr << "Error opening file\n";
            }
            throw std::exception("Exclusion due to the FATALERROR-type message\n");
        }
        else if (NextHandler != nullptr) {
            NextHandler->LogRequest(type, message);
        }
        else {
            std::cout << "Unknown type " << message << "\n";
        }
    }
};

// Обработчик неизвестной ошибки
class UnknownHandler : public LogMessage {
private:
    std::shared_ptr<LogMessage>  NextHandler = nullptr;
public:
    void SetNextHandler(std::shared_ptr<LogMessage>  handler) override {
        NextHandler = handler;
    }

    void LogRequest(Type type, std::string const& message) override {
        if (type == Type::UNKNOWN) {
            throw std::exception("Exclusion due to the UNKNOWN-type message\n");
        }
        else if (NextHandler != nullptr) {
            NextHandler->LogRequest(type, message);
        }
        else {
            std::cout << "Unknown type " << message << "\n";
        }
    }
};

int main()
{
    // Создание обработчиков
    auto msgWar = std::make_shared<WarringHandler>();
    auto msgErr = std::make_shared<ErrorHandler>();
    auto msgFat = std::make_shared<FatalHandler>();
    auto msgUnk = std::make_shared<UnknownHandler>();

    // Задание последовательности вызова обаботчиков
    msgWar->SetNextHandler(msgErr);
    msgErr->SetNextHandler(msgFat);
    msgFat->SetNextHandler(msgUnk);

    try {
        msgWar->LogRequest(Type::WARRING, "Warring message");
        std::cout << std::endl;
        msgErr->LogRequest(Type::ERROR, "Error message");
        std::cout << std::endl;
        //msgWar->LogRequest(Type::UNKNOWN, "Unknown error message");
        //std::cout << std::endl;
        msgWar->LogRequest(Type::FATALERROR, "Fatal error message");
        std::cout << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}