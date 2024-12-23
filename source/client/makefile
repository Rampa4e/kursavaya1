# Определяем переменные для путей
SRC_DIR = .
TARGET = client

# Определяем компилятор и флаги компиляции
CXX = g++
CXXFLAGS = -std=c++11 -lcryptopp

# Получаем список всех файлов .cpp в корневой директории
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Определяем все объектные файлы
OBJS = $(SOURCES:.cpp=.o)

# Цель по умолчанию
all: $(SRC_DIR)/$(TARGET) clean

# Сборка проекта
$(SRC_DIR)/$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)
	@echo "build complete."

# Правило для компиляции объектных файлов
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Очистка сборки
clean:
	@rm -f $(SRC_DIR)/*.o
	@echo "clean complete."

.PHONY: all clean
