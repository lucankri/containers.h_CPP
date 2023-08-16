#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_
#include <iostream>
#include <initializer_list>

namespace s21 {
    /**
     * @brief Array (массив) - это последовательный контейнер, инкапсулирующий в себе статический массив.
     * @details Так же как и vector, array занимает последовательную часть памяти
     * и может быть передан в функцию как стандартный массив в Си.
     * 
     * @tparam T - тип
     * @tparam std::size_t - фактический размер статического массива 
     */
    template<typename T, std::size_t Size>
    class array {
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;
        public:
            using iterator = T*;
            using const_iterator = const T*;

            /*------------------constructors and operators array----------------------*/

            /**
             * @brief Конструктор по умолчанию, создает пустой массив
             * @details Оставляем его дефолдным так как наш массив статический
             * и он уже инициализирован
             */
            array() = default;

            /**
             * @brief Конструктор списка инициализаторов, создает массив
             * @details Если количество элементов в списке не будет совбадать
             * с фактическим размером, будем выводить исключение
             * 
             * @param items 
             */
            array(std::initializer_list<value_type> const &items) {
                if (items.size() != Size)
                    throw std::runtime_error("s21::array: Initializer_list's size is not the same as the array's size!");

                auto it = items.begin();
                for (size_type i = 0; i < Size; i++) {
                    array_[i] = it[i];
                }
            }
            
            /**
             * @brief Конструктор копирования
             * 
             * @param a 
             */
            array(const array &a) {
                *this = a;
            }

            /**
             * @brief Конструктор перемещения
             * 
             * @param a 
             */
            array(array &&a) {
                *this = std::move(a);
            }

            /**
             * @brief Деструктор
             * @details Массив статический, поэтому деструктор
             * будет поумолчанию
             */
            ~array() = default;

            /**
             * @brief Оператор присваивания копированием
             * 
             * @param other 
             * @return array& 
             */
            array& operator=(const array &a) {
                if (this != &a) {
                    for (size_type i = 0; i < Size; i++) {
                        this->array_[i] = a.array_[i];
                    }
                }
                return *this;
            }

            /**
             * @brief Оператор присваивания перемещением
             * @details Мы не копируем, а забираем элементы
             * @param a 
             * @return array& 
             */
            array& operator=(array &&a) {
                if (this != &a) {
                    for (size_type i = 0; i < Size; i++) {
                        this->array_[i] = std::move(a.array_[i]);
                    }
                }
                return *this;
            }


            /*------------------------------------------------------------------------*/

            /*------------------------methods array-------------------------*/

            /**
             * @brief Доступ к указанному элементу с проверкой границ
             * 
             * @param pos 
             * @return reference 
             */
            reference at(size_type pos) {
                if (pos >= Size)
                    throw std::out_of_range("s21::array::at: Position out of range");

                return this->array_[pos];
            }

            /**
             * @brief Доступ к указанному элементу с проверкой границ
             * @details Для конст объектов
             * 
             * @param pos 
             * @return reference 
             */
            const_reference at(size_type pos) const {
                if (pos >= Size)
                    throw std::out_of_range("s21::array::at: Position out of range");

                return this->array_[pos];
            }

            /**
             * @brief Доступ к указанному элементу
             * 
             * @param pos 
             * @return reference 
             */
            reference operator[](size_type pos) {
                return this->at(pos);
            }

            /**
             * @brief Доступ к указанному элементу
             * @details Для конст объектов
             * 
             * @param pos 
             * @return reference 
             */
            const_reference operator[](size_type pos) const {
                return this->at(pos);
            }

            /**
             * @brief Получить доступ к первому элементу
             * @details Если контейнер пустой - выводим исключение
             * 
             * @return const_reference 
             */
            reference front() {
                if (Size == 0)
                    throw std::out_of_range("s21::array::front: empty container!");

                return *this->array_;
            }

            /**
             * @brief Получить доступ к первому элементу
             * @details Если контейнер пустой - выводим исключение.
             * Для конст объектов
             * 
             * @return const_reference 
             */
            const_reference front() const {
                if (Size == 0)
                    throw std::out_of_range("s21::array::front: empty container!");

                return *this->array_;
            }

            /**
             * @brief Получить доступ к последнем элементу
             * @details Тоже самое что и у front():
             * если контейнер пустой - выводим исключение
             * 
             * @return const_reference 
             */
            reference back() {
                if (Size == 0)
                    throw std::out_of_range("s21::array::back: empty container!");

                return *(this->array_ + (Size - 1));
            }

            /**
             * @brief Получить доступ к последнем элементу
             * @details Тоже самое что и у front():
             * если контейнер пустой - выводим исключение.
             * Для конст объектов
             * 
             * @return const_reference 
             */
            const_reference back() const {
                if (Size == 0)
                    throw std::out_of_range("s21::array::back: empty container!");

                return *(this->array_ + (Size - 1));
            }

            /**
             * @brief Прямой доступ к базовому массиву
             * 
             * @return iterator 
             */
            iterator data() noexcept {
                return this->array_;
            }

            /**
             * @brief Прямой доступ к базовому массиву
             * @details для конст объектов
             * 
             * @return iterator 
             */
            const_iterator data() const noexcept {
                return this->array_;
            }

            /**
             * @brief Возвращает итератор в начало
             * 
             * @return iterator 
             */
            iterator begin() noexcept {
                return this->array_;
            }

            /**
             * @brief Возвращает итератор в начало
             * @details Для конст объектов
             * 
             * @return iterator 
             */
            const_iterator begin() const noexcept {
                return this->array_;
            }

            /**
             * @brief Возвращает итератор в конец
             * 
             * @return iterator 
             */
            iterator end() noexcept {
                return this->array_ + Size;
            }

            /**
             * @brief Возвращает итератор в конец
             * 
             * @return iterator 
             */
            const_iterator end() const noexcept {
                return this->array_ + Size;
            }

            /**
             * @brief Проверяет, пуст ли контейнер
             * 
             * @return true - контейнер пуст
             * @return false - контейнер не пуст
             */
            bool empty() const noexcept {
                return Size == 0;
            }

            /**
             * @brief Возвращает количество элементов
             * 
             * @return size_type 
             */
            size_type size() const noexcept {
                return Size;
            }

            /**
             * @brief Возвращает максимально возможное количество элементов
             * @details Массив статический он не изсменится, поэтому
             * максимальное количество это и будет сколько в шаблоне Size
             * 
             * @return size_type 
             */
            size_type max_size() const noexcept {
                return Size;
            }

            /**
             * @brief Меняет содержимое
             * 
             * @param other 
             */
            void swap(array& other) noexcept {
                std::swap_ranges(this->begin(), this->end(), other.begin());
            }

            /**
             * @brief Присваивает заданное значение value всем элементам в контейнере.
             * 
             * @param value 
             */
            void fill(const_reference value) {
                for (size_type i = 0; i < Size; i++) {
                    this->array_[i] = value;
                }
            }

            /*-----------------------------------------------------------------------*/
        private:
            value_type array_[Size] = {};
    };
}

#endif // S21_ARRAY_H_