#include <string>
#include <iostream>

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};

class DecoratedText : public Text {
protected:    
    std::shared_ptr<Text> text_;
public:
    explicit DecoratedText(std::shared_ptr<Text> text) : text_(text) {}
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

class Paragraph : public DecoratedText {
public:
    explicit Paragraph(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};
    
class Reversed : public DecoratedText {
public:
    explicit Reversed(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::string tmp = data;
        std::reverse(tmp.begin(), tmp.end());
        text_->render(tmp);
    }
};

class Link : public DecoratedText {
public:
    explicit Link(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& url, const std::string& data)  const {
        std::cout << "<a href = ";
        text_->render(url);
        std::cout << ">";
        text_->render(data);
        std::cout << "</a>";
    }
};

int main() {
    auto text_block = std::make_shared<ItalicText>(std::make_shared<BoldText>(std::make_shared<Text>()));
    text_block->render("Hello world");
    std::cout << std::endl;

    auto text_block1 = std::make_shared<Paragraph>(std::make_shared <Text>());
    text_block1->render("Hello world");
    std::cout << std::endl;
  
    auto text_block2 = std::make_shared <Reversed>(std::make_shared <Text>());
    text_block2->render("Hello world");
    std::cout << std::endl;
    
    auto text_block3 = std::make_shared <Link>(std::make_shared <Text>());
    text_block3->render("netology.ru", "Hello world");
    std::cout << std::endl;
}