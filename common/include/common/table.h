#pragma once

#include <vector>

template<typename T>
class Table {
public:
    std::vector<std::vector<T>> data;

    Table() = default;
    Table(size_t rows, size_t columns, T value) : data(rows, std::vector<T>(columns, value)) {}

    [[nodiscard]] size_t rowCount() const {
        return data.size();
    }

    [[nodiscard]] size_t columnCount() const {
        return data.empty() ? 0 : data[0].size();
    }

    T& operator()(size_t row, size_t column) {
        return data[row][column];
    }

    const T& operator()(size_t row, size_t column) const {
        return data[row][column];
    }

    std::vector<T>& operator[](size_t row) {
        return data[row];
    }

    const std::vector<T>& operator[](size_t row) const {
        return data[row];
    }

    auto begin() const {
        return data.begin();
    }

    auto end() const {
        return data.end();
    }

    auto cbegin() const {
        return data.cbegin();
    }

    auto cend() const {
        return data.cend();
    }

    void transpose() {
        if (data.empty()) {
            return;
        }

        std::vector<std::vector<T>> transposed;
        for (size_t i = 0; i < data.size(); i++) {
            for (size_t j = 0; j < data[i].size(); j++) {
                transposed[j][i] = data[i][j];
            }
        }
        data = std::move(transposed);
    };
};

// specialization for bool
template<>
class Table<bool> {
public:
    std::vector<std::vector<char>> data;

    Table() = default;
    Table(size_t rows, size_t columns, bool value) : data(rows, std::vector<char>(columns, toChar(value))) {}

    [[nodiscard]] size_t rowCount() const {
        return data.size();
    }

    [[nodiscard]] size_t columnCount() const {
        return data.empty() ? 0 : data[0].size();
    }

    bool operator()(size_t row, size_t column) const {
        return toBool(data[row][column]);
    }

    void set(size_t row, size_t column, bool value) {
        data[row][column] = toChar(value);
    }

private:
    static bool toBool(char c) {
        return c == '1';
    }

    static char toChar(bool b) {
        return b ? '1' : '0';
    }
};

struct TableCell {
    size_t row;
    size_t column;

    bool operator==(const TableCell& other) const = default;
};

struct TableStep {
    int rowDiff;
    int columnDiff;
};

template<typename T>
struct TableRegion {
    std::vector<TableCell> cells;
    T value;
    int perimeter = 0;
    int corners = 0;

    bool contains(size_t row, size_t column) {
        return std::ranges::find(cells, TableCell{row, column}) != cells.end();
    }

    int area() const {
        return cells.size();
    }
};
