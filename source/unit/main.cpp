#include "error.h"
#include "vclient.h"
#include "rw.h"
#include "cmd.h"
#include "md5.h"

#include "UnitTest++/UnitTest++.h"
#include <fstream>
#include <cstdio> // для функции remove

// Тесты для CMDParser
TEST(CMDParser_DefaultValues) {
    CMDParser parser;
    CHECK_EQUAL("./in.txt", parser.getIn());
    CHECK_EQUAL("./out.bin", parser.getOut());
    CHECK_EQUAL("./cfg.txt", parser.getCfg());
    CHECK_EQUAL("127.0.0.1", parser.getAddr());
    CHECK_EQUAL(33333, parser.getPort());
}

TEST(CMDParser_ParseArgs) {
    CMDParser parser;
    const char* argv[] = {"program", "-i", "input.txt", "-o", "output.bin", "-c", "config.txt", "-a", "192.168.0.1", "-p", "12345"};
    parser.parse(11, const_cast<char**>(argv));
    CHECK_EQUAL("input.txt", parser.getIn());
    CHECK_EQUAL("output.bin", parser.getOut());
    CHECK_EQUAL("config.txt", parser.getCfg());
    CHECK_EQUAL("192.168.0.1", parser.getAddr());
    CHECK_EQUAL(12345, parser.getPort());
}

TEST(CMDParser_InvalidArgs) {
    CMDParser parser;
    const char* argv[] = {"program", "--in"};
    CHECK_THROW(parser.parse(2, const_cast<char**>(argv)), VClientError);
}

// Тесты для ReadWrite
TEST(ReadWrite_Initialization) {
    string inVec = "input.txt";
    string outVec = "output.bin";
    string cfg = "config.txt";
    ReadWrite rw(inVec, outVec, cfg);
    CHECK_EQUAL("input.txt", rw.getIn());
    CHECK_EQUAL("output.bin", rw.getOut());
    CHECK_EQUAL("config.txt", rw.getCfg());
}

TEST(ReadWrite_WriteVec) {
    string inVec = "input.txt";
    string outVec = "output.bin";
    string cfg = "config.txt";
    ReadWrite rw(inVec, outVec, cfg);

    vector<int32_t> data = {1, 2, 3, 4};
    rw.writeVec(data);

    // Чтение файла и проверка его содержимого
    ifstream infile(outVec, ios::binary);
    CHECK(infile.is_open());

    uint32_t vec_size;
    infile.read(reinterpret_cast<char*>(&vec_size), sizeof(vec_size));
    CHECK_EQUAL(data.size(), vec_size);

    vector<int32_t> read_data(vec_size);
    infile.read(reinterpret_cast<char*>(read_data.data()), vec_size * sizeof(int32_t));
    CHECK_ARRAY_EQUAL(data, read_data, vec_size);

    infile.close();

    // Удаление файла после теста
    remove(outVec.c_str());
}

TEST(ReadWrite_WriteVec_FileError) {
    string inVec = "input.txt";
    string outVec = "/invalid/path/output.bin"; // Неверный путь
    string cfg = "config.txt";
    ReadWrite rw(inVec, outVec, cfg);

    vector<int32_t> data = {1, 2, 3, 4};
    CHECK_THROW(rw.writeVec(data), VClientError);
}

TEST(ReadWrite_ReadVec) {
    string inVec = "input.txt";
    string outVec = "output.bin";
    string cfg = "config.txt";

    // Запись тестовых данных в файл
    ofstream outfile(inVec);
    outfile << "2\n";
    outfile << "3\n1 2 3\n";
    outfile << "2\n4 5\n";
    outfile.close();

    ReadWrite rw(inVec, outVec, cfg);
    vector<vector<int32_t>> vectors = rw.readVec();

    CHECK_EQUAL(2, vectors.size());
    CHECK_ARRAY_EQUAL(vector<int32_t>({1, 2, 3}), vectors[0], 3);
    CHECK_ARRAY_EQUAL(vector<int32_t>({4, 5}), vectors[1], 2);

    // Удаление файла после теста
    remove(inVec.c_str());
}

TEST(ReadWrite_ReadVec_FileError) {
    string inVec = "/invalid/path/input.txt"; // Неверный путь
    string outVec = "output.bin";
    string cfg = "config.txt";
    ReadWrite rw(inVec, outVec, cfg);

    CHECK_THROW(rw.readVec(), VClientError);
}

TEST(ReadWrite_ReadCfg) {
    string inVec = "input.txt";
    string outVec = "output.bin";
    string cfg = "config.txt";

    // Запись тестовых данных в файл конфигурации
    ofstream cfgfile(cfg);
    cfgfile << "user:password\n";
    cfgfile.close();

    ReadWrite rw(inVec, outVec, cfg);
    array<string, 2> configArray = rw.readCfg();

    CHECK_EQUAL("user", configArray[0]);
    CHECK_EQUAL("password", configArray[1]);

    // Удаление файла после теста
    remove(cfg.c_str());
}

TEST(ReadWrite_ReadCfg_FileError) {
    string inVec = "input.txt";
    string outVec = "output.bin";
    string cfg = "/invalid/path/config.txt"; // Неверный путь
    ReadWrite rw(inVec, outVec, cfg);

    CHECK_THROW(rw.readCfg(), VClientError);
}

// Тесты для функций хеширования
TEST(MD5_Hashing) {
    string data = "hello";
    string hash = md5(data);
    CHECK_EQUAL("5D41402ABC4B2A76B9719D911017C592", hash);
}

// Тесты для VClient
TEST(VClient_Initialization) {
    array<string, 2> conf = {"user", "password"};
    VClient client("127.0.0.1", 33333, conf);
    CHECK_EQUAL("127.0.0.1", client.getAddr());
    CHECK_EQUAL(33333, client.getPort());
    CHECK(conf[0] == "user");
    CHECK(conf[1] == "password");
}

int main(int argc, char* argv[]) {
    return UnitTest::RunAllTests();
}
