#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <filesystem>

#include <MultiGenerator/Context/Stream.hpp>

namespace Context = MultiGenerator::Context;

void testStandardInputStream() {
    using Context::StandardInputStream;

    {
        StandardInputStream is;
        assert(std::addressof(is.getStream()) == std::addressof(std::cin));
    }
}

void testFileInputStream() {
    using Context::FileInputStream;

    {
        {
            std::ofstream ofs("tmp.txt");
            ofs << "test" << std::endl;
        }

        {
            FileInputStream is("tmp.txt");
            std::string str;
            is.getStream() >> str;
            assert(str == "test");
        }
        
        {
            std::filesystem::path p("tmp.txt");
            std::filesystem::remove(p);
        }
    }
}

void testInputStream() {
    using Context::InputStream;
    using Context::StandardInputStream;
    using Context::FileInputStream;
    
    {
        {
            // Create a file named tmp.txt.
            std::ofstream ofs("tmp.txt");
            ofs << "test" << std::endl;
        }
        
        {
            std::shared_ptr<InputStream> ptrA = std::make_shared<StandardInputStream>();
            std::shared_ptr<InputStream> ptrB = std::make_shared<FileInputStream>("tmp.txt");
            assert(std::addressof(ptrA->getStream()) == std::addressof(std::cin));
            assert(std::addressof(ptrB->getStream()) != std::addressof(std::cin));

            std::string str;
            ptrB->getStream() >> str;
            assert(str == "test");
        }

        {
            std::filesystem::path p("tmp.txt");
            std::filesystem::remove(p);
        }
    }
}

void testStandardOutputStream() {
    using Context::StandardOutputStream;

    {
        StandardOutputStream os;
        assert(std::addressof(os.getStream()) == std::addressof(std::cout));
    }
}

void testFileOutputStream() {
    using Context::FileOutputStream;
    
    {
        {
            FileOutputStream ofs("tmp.txt");
            ofs.getStream() << "test" << std::endl;
        }

        {

            std::ifstream ifs("tmp.txt");
            std::string str;
            ifs >> str;
            assert(str == "test");
        }
        
        {
            std::filesystem::path p("tmp.txt");
            std::filesystem::remove(p);
        }
    }
}

void testOutputStream() {
    using Context::OutputStream;
    using Context::StandardOutputStream;
    using Context::FileOutputStream;
    
    {
        {
            std::shared_ptr<OutputStream> ptrA = std::make_shared<StandardOutputStream>();
            std::shared_ptr<OutputStream> ptrB = std::make_shared<FileOutputStream>("tmp.txt");
            assert(std::addressof(ptrA->getStream()) == std::addressof(std::cout));
            assert(std::addressof(ptrB->getStream()) != std::addressof(std::cout));

            ptrB->getStream() << "test" << std::endl;
        }

        {
            std::ifstream ifs("tmp.txt");
            std::string str;
            ifs >> str;
            assert(str == "test");
        }

        {
            std::filesystem::path p("tmp.txt");
            std::filesystem::remove(p);
        }
    }
}

int main() {
    testStandardInputStream();
    testFileInputStream();
    testInputStream();
    testStandardOutputStream();
    testFileOutputStream();
    testOutputStream();
    return 0;
}