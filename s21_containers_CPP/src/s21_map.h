#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_
#include "s21_tree.h"
#include <iostream>

namespace s21 {
    /**
     * @brief Map (словарь) - это ассоциативный контейнер, содержащий отсортированные
     * по возрастанию ключа пары ключ-значение.
     * @details Тоесть каждый элемент ассоциирован с некоторым уникальным ключом,
     * и его положение в словаре определяется его ключом.Словари удобно применять,
     * когда необходимо ассоциировать элементы с некоторым другим значением (не индексом).
     * Реализов через tree (дерева), его реализацию смотрите в s21_tree.h
     *
     */
    template<typename Key, typename T>
    class map {
        class MapComparatorMy;
        using key_type = Key;
        using mapped_type = T;
        using value_type = std::pair<const key_type, mapped_type>;
        using reference = value_type&;
        using const_reference = const value_type&;
        using tree = BinaryTree<value_type, MapComparatorMy>;
        using size_type = std::size_t;
        // Так как мы будем искать значения по ключу, а у нас два значения в pair 
        // - нам нужен свой компаратор
        class MapComparatorMy {
            public:
                //Перегружаем оператор таким образом, чтоб он проверял только ключи
                bool operator()(const_reference v1, const_reference v2) const noexcept {
                    return v1.first < v2.first;
                }
        };

        public:
            using iterator = typename tree::iterator;
            using const_iterator = typename tree::const_iterator;

            /*------------------constructors and operators map----------------------*/

            /**
             * @brief Конструктор по умолчанию, создает пустой словарь
             * 
             */
            map() : tree_() {}

            /**
             * @brief конструктор списка инициализаторов, создает словарь уже с элементами
             * 
             * @param items 
             */
            map(std::initializer_list<value_type> const &items) : tree_() {
                for (auto element : items) {
                    this->tree_.insertUnique(element);
                }
            }

            /**
             * @brief Конструктор копирования
             * 
             * @param m 
             */
            map(const map &m) : tree_(m.tree_) {}

            /**
             * @brief Конструктор перемещения
             * 
             * @param m 
             */
            map(map &&m) : tree_(std::move(m.tree_)) {}

            /**
             * @brief Деструктор будет дефолдным
             * @details tree_ сам себя почистит, у него есть свой деструктор
             * 
             */
            ~map() = default;

            /**
             * @brief Перегрузка оператора присваивания копированием
             * 
             * @param m 
             * @return map& 
             */
            map& operator=(const map &m) {
                this->tree_ = m.tree_;
                return *this;
            }

            /**
             * @brief Перегрузка оператора присваивания перемещением
             * 
             * @param m
             * @return map& 
             */
            map& operator=(map &&m) {
                this->tree_ = std::move(m.tree_);
                return *this;
            }

            /*------------------------------------------------------------------------------*/

            /*------------------------methods map-------------------------*/

            /**
             * @brief Доступ к указанному элементу с проверкой границ
             * @details Если такого элемента нет, значит будет исключение
             * 
             * @param key 
             * @return T& 
             */
            mapped_type& at(const Key& key) {
                // создаем pair для поиска ключа
                // так как в дереве теперь наш компаратор
                value_type pair = {key, mapped_type{}};
                iterator it = this->tree_.find(pair);
                // проверяем, если it == end() зачит ключа в контейнере нет
                if (it == this->tree_.end())
                    throw std::out_of_range("s21::map::at: no such element exists");
                
                return (*it).second;
            }

            /**
             * @brief Доступ к указанному элементу с проверкой границ
             * @details Если такого элемента нет, значит будет исключение.
             * Для конст объекта
             * 
             * @param key 
             * @return T& 
             */
            const mapped_type& at(const Key& key) const {
                return const_cast<map<key_type, mapped_type> *>(this)->at(key);
            }

            /**
             * @brief Получить доступ или вставить указанный элемент
             * @details Если такого ключа нет, произойдет вставка с тим ключем
             * инициализация mapped_type будет дефолдным
             * 
             * @param key 
             * @return mapped_type& 
             */
            mapped_type& operator[](const Key& key) {
                // создаем pair для поиска
                value_type pair = {key, mapped_type{}};
                iterator it = this->tree_.find(pair);
                if (it == this->tree_.end()) {
                    // если такого элемента нет, значит вставляем его
                    // с дефолдным значением
                    std::pair<iterator, bool> res = this->tree_.insertUnique(pair);
                    return (*res.first).second;
                }
                // если есть тогда выводим то что нашли
                return (*it).second;
            }

            /**
             * @brief Возвращает итератор в начало
             * 
             * @return iterator 
             */
            iterator begin() noexcept {
                return this->tree_.begin();
            }

            /**
             * @brief Возвращает итератор в начало
             * @details Для конст объекта
             * 
             * @return const_iterator 
             */
            const_iterator begin() const noexcept {
                return this->tree_.begin();
            }

            /**
             * @brief Возвращает итератор в конец
             * 
             * @return iterator 
             */
            iterator end() noexcept {
                return this->tree_.end();
            }

            /**
             * @brief Возвращает итератор в конец
             * @details Для конст объекта
             * 
             * @return const_iterator
             */
            const_iterator end() const noexcept {
                return this->tree_.end();
            }

            /**
             * @brief Проверяет, пуст ли контейнер
             * 
             * @return true - контейнер пуст
             * @return false - контейнер не пуст
             */
            bool empty() const noexcept {
                return this->tree_.empty();
            }

            /**
             * @brief Возвращает количество элементов
             * 
             * @return size_type 
             */
            size_type size() const noexcept {
                return this->tree_.size();
            }

            /**
             * @brief Возвращает максимально возможное количество элементов
             * @details Алгоритм логики ищите в s21_tree
             * 
             * @return size_type 
             */
            size_type max_size() const noexcept {
                return this->tree_.max_size();
            }

            /**
             * @brief Очищает содержимое контейнера
             * 
             */
            void clear() noexcept {
                return this->tree_.clear();
            }

            /**
             * @brief вставляет узел и возвращает итератор туда, где элемент находится
             * в контейнере, и логическое значение, обозначающее, имела ли место вставка
             * 
             * @param value 
             * @return std::pair<iterator, bool> 
             */
            std::pair<iterator, bool> insert(const value_type& value) {
                return this->tree_.insertUnique(value);
            }

            /**
             * @brief вставляет значение по ключу и возвращает итератор туда, где элемент находится в контейнере,
             * и логическое значение, обозначающее, имела ли место вставка
             * @details вставка может не произойти если уже ключ имеется,
             * тогда веренм пару из iterator - указывающий на end() и bool - false
             * 
             * @param key 
             * @param obj 
             * @return std::pair<iterator, bool> 
             */
            std::pair<iterator, bool> insert(const Key& key, const mapped_type& obj) {
                return this->tree_.insertUnique({key, obj});
            }

            /**
             * @brief Вставляет элемент или присваивает значение текущему элементу, если ключ уже существует
             * @details Если ключ уже такой есть, значит меняем только значение по ключу который нашли и
             * возвращаем пару: iterator - указывает на этот элемент, bool - false, так как новая
             * вставка не произошла
             * 
             * @param key 
             * @param obj 
             * @return std::pair<iterator, bool> 
             */
            std::pair<iterator, bool> insert_or_assign(const Key& key, const mapped_type& obj) {
                value_type pair = {key, obj};
                iterator it = this->tree_.find(pair);
                if (it == this->tree_.end())
                    return this->tree_.insertUnique(pair);
                
                (*it).second = obj;
                return {it, false};
            }

            /**
             * @brief Стирает элемент в позиции
             * 
             * @param pos 
             */
            void erase(iterator pos) noexcept {
                this->tree_.erase(pos);
            }

            /**
             * @brief Меняет содержимое
             * 
             * @param other 
             */
            void swap(map& other) noexcept {
                std::swap(this->tree_, other.tree_);
            }

            /**
             * @brief Соединяет узлы из другого контейнера
             * 
             * @param other 
             */
            void merge(map& other) {
                this->tree_.mergeUnique(other.tree_);
            }

            /**
             * @brief Проверяет, есть ли элемент с ключом, эквивалентным ключу в контейнере
             * 
             * @param key 
             * @return true - есть элемент в контенере
             * @return false - нет эдемента в контейнере
             */
            bool contains(const Key& key) const {
                return this->tree_.find({key, mapped_type{}}) != this->tree_.end();
            }

            /**
             * @brief Вставляет новые элеметы в контейнер, если контейнер
             * не содержит таких ключей
             * 
             * @tparam Args 
             * @param args 
             * @return std::vector<std::pair<iterator,bool>> 
             */
            template<typename... Args>
            std::vector<std::pair<iterator,bool>> emplace(Args&&... args) {
                return this->tree_.emplaceUnique(std::forward<Args>(args)...);
            }

        private:
            tree tree_;

    }; // map
} // s21

#endif //SRC_S21_MAP_H_