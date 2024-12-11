#pragma once

#include <vector>

template<typename T>
struct Table {
    std::vector<std::vector<T>> data;

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