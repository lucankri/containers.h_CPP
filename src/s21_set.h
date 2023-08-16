#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_
#include "s21_tree.h"

namespace s21 {
    /**
     * @brief Set (множество) - это ассоциативный контейнер уникальных элементов.
     * @details Это означает, что в множество нельзя добавить один и тот же элемент дважды.
     * Контейнер множество является ассоциативным, так как внутри он также представлен в виде дерева,
     * как и контейнер map (словарь), и, соответственно, также хранит элементы в отсортированном порядке.
     * Реализов через tree (дерева), его реализацию смотрите в s21_tree.h
     */
    template<typename Key>
    class set {
        using key_type = Key;
        using value_type = Key;
        using reference = value_type&;
        using const_reference = const value_type&;
        using tree = BinaryTree<Key>;
        using size_type = std::size_t;
        public:
            using iterator = typename tree::iterator;
            using const_iterator = typename tree::const_iterator;


            /*------------------constructors and operators set----------------------*/

            /**
             * @brief Конструктор по умолчанию, создает пустой набор
             * 
             */
            set() : tree_() {}

            /**
             * @brief Конструктор списка инициализаторов, создает набор
             * 
             */
            set(std::initializer_list<value_type> const &items) : tree_() {
                for (auto element : items) {
                    this->tree_.insertUnique(element);
                }
            }

            /**
             * @brief Конструктор копирования
             * 
             * @param s 
             */
            set(const set &s) : tree_(s.tree_) {}

            /**
             * @brief Конструктор перемещения
             * 
             * @param s 
             */
            set(set &&s) : tree_(std::move(s.tree_)) {}

            /**
             * @brief Деструктор будет дефолдным
             * @details tree_ сам себя почистит, у него есть свой деструктор
             * 
             */
            ~set() = default;

            /**
             * @brief Перегрузка оператора присваивания копированием
             * 
             * @param s 
             * @return set& 
             */
            set& operator=(set &s) {
                this->tree_ = s.tree_;
                return *this;
            }

            /**
             * @brief Перегрузка оператора присваивания перемещением
             * 
             * @param s 
             * @return set& 
             */
            set& operator=(set &&s) {
                this->tree_ = std::move(s.tree_);
                return *this;
            }

            /*------------------------------------------------------------------------*/

            /*------------------------methods set-------------------------*/

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
             * @details Для конст обЪекта
             * 
             * @return const_iterator 
             */
            const_iterator begin() const noexcept {
                return this->tree_.begin();
            }

            /**
             * @brief Возвращает итератор в конец
             * 
             * 
             * @return iterator 
             */
            iterator end() noexcept {
                return this->tree_.end();
            }

            /**
             * @brief Возвращает итератор в конец
             * @details Для конст обЪекта
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
             * @details Алгоритм как высчитвается смотрите в s21_tree.h
             * 
             * @return size_type
             */
            size_type max_size() const noexcept {
                return this->tree_.max_size();
            }

            /**
             * @brief Очищает содержимое
             * 
             */
            void clear() noexcept {
                this->tree_.clear();
            }


            /**
             * @brief Вставляет элемент со значением в контейнер,
             * вставляет только уникальные элементы
             * 
             * @param value 
             * @return std::pair<iterator, bool> возвращает итератор где находится этот элемент и
             * логическое значение (имела ли место вставка или нет)
             */
            std::pair<iterator, bool> insert(const value_type& value) {
                return this->tree_.insertUnique(value);
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
            void swap(set& other) noexcept {
                std::swap(this->tree_, other.tree_);
            }

            /**
             * @brief Cоединяет узлы из другого контейнера
             * 
             * @param other 
             */
            void merge(set& other) {
                this->tree_.mergeUnique(other.tree_);
            }

            /**
             * @brief Находит элемент с определенным ключом
             * 
             * @param key 
             * @return iterator - если элемента нет в контейнере - итератор
             * будет указывать на end()
             */
            iterator find(const Key& key) {
                return this->tree_.find(key);
            }

            /**
             * @brief Находит элемент с определенным ключом
             * @details Для конст объекта
             * 
             * @param key 
             * @return iterator - если элемента нет в контейнере - итератор
             * будет указывать на end()
             */
            const_iterator find(const Key& key) const {
                return this->tree_.find(key);
            }

            /**
             * @brief Проверяет, содержит ли контейнер элемент с определенным ключом
             * 
             * @param key 
             * @return true - в контейнере есть этот элемент
             * @return false - в контенер нет этого элемента
             */
            bool contains(const Key& key) const {
                return this->tree_.find(key) != this->tree_.end();
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


            /*------------------------------------------------------------*/

        private:
            tree tree_;

    }; // set
} // s21




#endif // SRC_S21_SET_H_