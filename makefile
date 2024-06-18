# Nombre del archivo ejecutable
TARGET = battleShip.exe

# Compilador
CC = g++

# Opciones de compilación
CFLAGS = -Wall -g

# Encuentra todos los archivos .cpp en el directorio actual
SOURCES = $(wildcard *.cpp)

# Nombres de los archivos objeto, basados en los archivos fuente
OBJECTS = $(SOURCES:.cpp=.o)

# Regla por defecto
all: $(TARGET)

# Cómo construir el objetivo final
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Cómo construir cada objeto a partir de los archivos CPP
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

# Comando para limpiar los archivos compilados
clean:
	rm -f $(OBJECTS) $(TARGET)