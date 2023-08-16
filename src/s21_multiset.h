#ifndef SRC_S21_MULTISET_H_
#define SRC_S21_MULTISET_H_
#include "s21_tree.h"

namespace s21 {
    /**
     * @brief Multiset (мультимножество) - это ассоциативный контейнер, повторяющий логику множества
     * но позволяющий хранить идентичные элементы.
     * @details Реализован через дерево точно так же как и set(), только в multiset ключи
     * могут повторятся в реализации s21_tree это предусмотренно
     * 
     * @tparam Key 
     */
    template<typename Key>
    class multiset {
        using key_type = Key;
        using value_type = Key;
        using reference = value_type&;
        using const_reference = const value_type&;
        using tree = BinaryTree<Key>;
        using size_type = std::size_t;
        public:
            using iterator = typename tree::iterator;
            using const_iterator = typename tree::const_iterator;

            /*------------------constructors and operators multiset----------------------*/
            
            /**
             * @brief Конструктор по умолчанию, создает пустой набор
             * 
             */
            multiset() : tree_() {}

            /**
             * @brief Конструктор списка инициализаторов, создает набор
             * 
             * @param items 
             */
            multiset(std::initializer_list<value_type> const &items) : tree_() {
                for (auto element : items) {
                    this->tree_.insert(element);
                }
            }

            /**
             * @brief Конструктор копирования
             * 
             * @param ms 
             */
            multiset(const multiset &ms) : tree_(ms.tree_) {}

            /**
             * @brief Конструктор перемещения
             * 
             * @param ms 
             */
            multiset(multiset &&ms) : tree_(std::move(ms.tree_)) {}

            /**
             * @brief Оператор присваивания копированием
             * 
             * @param ms 
             * @return multiset& 
             */
            multiset& operator=(multiset &ms) {
                this->tree_ = ms.tree_;
                return *this;
            }

            /**
             * @brief Оператор присваивания перемещением
             * 
             * @param ms 
             * @return multiset& 
             */
            multiset& operator=(multiset &&ms) {
                this->tree_ = std::move(ms.tree_);
                return *this;
            }

            /*----------------------------------------------------------------------*/

            /*------------------------methods multiset-------------------------*/

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
             * 
             * @return size_type 
             */
            size_type max_size() const noexcept {
                return this->tree_.max_size();
            }
            

            /**
             * @brief Очищает содержимое в контейнере
             * 
             */
            void clear() noexcept {
                this->tree_.clear();
            }

            /**
             * @brief Вставляет узел и возвращает итератор туда, где элемент находится в контейнере
             * 
             * @param value 
             * @return iterator 
             */
            iterator insert(const value_type& value) {
                return this->tree_.insert(value);
            }

            /**
             * @brief Стирает элемент в позиции
             * 
             * @param pos 
             */
            void erase(iterator pos) {
                this->tree_.erase(pos);
            }

            /**
             * @brief Меняет содержимое
             * 
             * @param other 
             */
            void swap(multiset& other) {
                std::swap(this->tree_, other.tree_);
            }


            /**
             * @brief Соединяет узлы из другого контейнера
             * 
             * @param other 
             */
            void merge(multiset& other) {
                this->tree_.merge(other.tree_);
            }

            /**
             * @brief Возвращает количество элементов, соответствующих определенному ключу
             * 
             * @param key 
             * @return size_type 
             */
            size_type count(const Key& key) const noexcept {
                size_type result = 0;
                auto it_search = this->lower_bound(key);
                for (auto it_end = this->end(); *it_search == key && it_search != it_end; ++result, ++it_search);
                return result;
            }

            /**
             * @brief Находит элемент с определенным ключом
             * 
             * @param key 
             * @return iterator 
             */
            iterator find(const Key& key) {
                return this->tree_.find(key);
            }

            /**
             * @brief Находит элемент с определенным ключом
             * @details Для конст объекта
             * 
             * @param key 
             * @return const_iterator 
             */
            const_iterator find(const Key& key) const {
                return this->tree_.find(key);
            }

            /**
             * @brief Проверяет, содержит ли контейнер элемент с определенным ключом
             * 
             * @param key 
             * @return true - есть такой элемент
             * @return false - нет такого элемента
             */
            bool contains(const Key& key) const noexcept {
                return *(this->tree_.find(key)) == key;
            }

            /**
             * @brief Возвращает диапазон элементов, соответствующих определенному ключу
             * @details Диапозон определяется двумя итераторами, один указывает на первый элемент
             * который не меньше ключа, второй указывает на первый элемент больше ключа.
             * Можно вызвать lower_bound и upper_bound, но тогда работать функция будет
             * медленее, так как два раза пробегаемся по дереву...
             * Можно вызвать lower_bound, а дальше просто посчитать - так мы и сделали
             * 
             * @param key 
             * @return std::pair<iterator,iterator> 
             */
            std::pair<iterator, iterator> equal_range(const Key& key) {
                iterator it_first = this->lower_bound(key);
                iterator it_second = it_first;
                while (*it_second == key) {
                    ++it_second;
                }
                return std::pair<iterator, iterator> {it_first, it_second};
            }

            /**
             * @brief Аналогично функции equal_range, для конст объекта
             * 
             * @param key 
             * @return std::pair<const_iterator, const_iterator> 
             */
            std::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
                const_iterator it_first = this->lower_bound(key);
                const_iterator it_second = it_first;
                while (*it_second == key) {
                    ++it_second;
                }
                return std::pair<const_iterator, const_iterator> {it_first, it_second};
            }

            /**
             * @brief Возвращает итератор к первому элементу не меньше заданного ключа
             * 
             * @param key 
             * @return iterator 
             */
            iterator lower_bound(const Key& key) {
                return this->tree_.lowerBound(key);
            }

            /**
             * @brief Возвращает итератор к первому элементу не меньше заданного ключа
             * @details Для конст объекта
             * 
             * @param key 
             * @return const_iterator 
             */
            const_iterator lower_bound(const Key& key) const {
                return this->tree_.lowerBound(key);
            }

            /**
             * @brief Возвращает итератор к первому элементу больше заданного ключа
             * 
             * @param key 
             * @return iterator 
             */
            iterator upper_bound(const Key& key) noexcept {
                return this->tree_.upperBound(key);
            }

            /**
             * @brief Возвращает итератор к первому элементу больше заданного ключа
             * @details Для конст объекта
             * 
             * @param key 
             * @return const_iterator 
             */
            const_iterator upper_bound(const Key& key) const noexcept{
                return this->tree_.upperBound(key);
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
                return this->tree_.emplace(std::forward<Args>(args)...);
            }

        private:
            tree tree_;
    }; // multiset
} // s21


#endif // SRC_S21_MULTISET_H_