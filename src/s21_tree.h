#ifndef SRC_S21_TREE_H_
#define SRC_S21_TREE_H_
#include <iostream>
#include <functional>
#include <limits>
#include <vector>

namespace s21 {
    /**
     * @brief ВАЖНО!!!
     * Реализация красно-черного дерева, почти весь функционал я буду описывать
     * так как в materials нет информации про бинарные деревеья!
     * Ссылка https://www.cs.usfca.edu/~galles/visualization/RedBlack.html - посмотреть
     * визуализацию красно-черного дерева, суть та же но наш алгоритм немножко отличается
     * 
     * @details Красно-черное дерево - один из видов самобалансирующихся двоичных деревьев поиска, где каждый
     * узел имеет черный или красный цвет и благодоря этому мы можем балансировать дерево
     * после вставки и удаления узла
     * У красно-черного дерева есть определенные правила:
     * 1. Корень — всегда чёрный;
     * 2. Узел может быть либо красным, либо чёрным и имеет двух потомков;
     * 3. У красного узла должно быть два черных потомка (Не может быть, что у красного узла - красный потомок);
     * 4. Все листья, не содержащие данных — чёрные (такие листья называют NIL);
     * 5. Любой простой путь от узла-предка до листового узла-потомка содержит
     * одинаковое число чёрных узлов (Этот путь называют "Черная высота");
     * 
     * Так же в нашей реализации имеется голова дерева (служебный узел, поле head_), он у нас будет красным):
     * head_->left_ - самый маленкий элемент;
     * head_->right_ - самый большой элемент;
     * head_->parent_ - корень дерево (который всегда черный); 
     */
    template<typename Key, typename Comparator = std::less<Key>>
    class BinaryTree {
        class BinaryTreeNode;
        class BinaryTreeIterator;
        class BinaryTreeConstIterator;
        using tree_node = BinaryTreeNode;
        using reference = Key&;
        using const_reference = const Key&;
        using size_type = std::size_t;
        enum colorRB {
            // Узлы могут быть красными и черными
            // будет в доступе private
            Black,
            Red
        };
        public:
            // итераторы переопределим в public как iterator и const_iterator
            using iterator = BinaryTreeIterator;
            using const_iterator = BinaryTreeConstIterator;

            /*----------------------------constructors and operators--------------------------------*/

            // Конструктор инициализации дерева, создает служебный узел для головы дерева
            BinaryTree() {
                this->head_ = new tree_node;
                this->size_ = 0;
            }

            // Конструктор копирования дерева
            BinaryTree(const BinaryTree& other) : BinaryTree() {
                *this = other;
            }


            // Конструктор перемещения дерева
            BinaryTree(BinaryTree&& other) : BinaryTree() {
                *this = std::move(other);
            }

            // Деструктор - удаления дерева
            ~BinaryTree() {
                this->clear();
                delete this->head_;
                this->head_ = nullptr;
            }

            // Оператор присваивания копированием
            BinaryTree& operator=(const BinaryTree& other) {
                if (this != &other) {
                    if (other.size_ == 0) {
                        this->clear();
                    } else {
                        tree_node* temp_root = this->copyFromNode(other.head_->parent_, nullptr);
                        this->clear();
                        this->head_->parent_ = temp_root;
                        this->head_->parent_->parent_ = this->head_;
                        this->head_->left_ = searchLeft(this->head_->parent_);
                        this->head_->right_ = searchRight(this->head_->parent_);
                        this->size_ = other.size_;
                        this->comparator_ = other.comparator_;
                    }
                }
                return *this;
            }


            // Оператор присваивания перемещением
            BinaryTree& operator=(BinaryTree&& other) {
                if (this != &other) {
                    this->clear();
                    std::swap(this->head_, other.head_);
                    std::swap(this->size_, other.size_);
                    std::swap(this->comparator_, other.comparator_);
                }
                return *this;
            }

            /*----------------------------------------------------------------------------------*/

            /*---------------------------------methods----------------------------------*/

            /**
             * @brief Функция удаления дерева, служебный узел head_ остается
             * 
             */
            void clear() {
                // Удаляем узлы
                this->destroyNodes(this->head_->parent_);
                // Приводим наше дерево к состоянию пустого дерева
                this->head_->parent_ = nullptr;
                this->head_->left_ = this->head_;
                this->head_->right_ = this->head_;
                this->size_ = 0;
            }

            /**
             * @brief Функция возвращает iterator указывающий на первый элемент(на самый левый(маленький) элемент)
             * 
             * @return iterator - начало
             */
            iterator begin() noexcept {
                return iterator(this->head_->left_);
            }

            /**
             * @brief Функция возвращает iterator указывающий на первый элемент(на самый левый(маленький) элемент)
             * @details Для конст объекта
             * 
             * @return const_iterator - начало
             */
            const_iterator begin() const noexcept {
                return const_iterator(this->head_->left_);
            }

            /**
             * @brief Функция возвращает iterator указывающий на служебный узел(head_ - голова нашего древа),
             * head_ будет концом нашего древа
             * 
             * @return iterator - конец
             */
            iterator end() noexcept {
                return iterator(this->head_);
            }

            /**
             * @brief Функция возвращает iterator указывающий на служебный узел(head_ - голова нашего древа),
             * head_ будет концом нашего древа
             * @details Для конст объкта
             * 
             * @return iterator - конец
             */
            const_iterator end() const noexcept {
                return const_iterator(this->head_);
            }

            /**
             * @brief Функция выводит количество элементов в дереве
             * @details В дереве есть служебный узел (head_), его в счет не берем.
             * 
             * @return size_type - количество узлов в дереве
             */
            size_type size() const noexcept {
                return this->size_;
            }

            /**
             * @brief Функция проверяет пустое ли дерево
             * 
             * @return true - пустое
             * @return false - непустое
             */
            bool empty() const noexcept {
                return this->size_ == 0;
            }

            /**
             * @brief Возвращает максимальное количество элементов, которое может
             * содержать дерево.
             * @details значение size_t - это максимальное количество байт памяти.
             * Это значение мы получаем при помощи std::numeric_limits<size_t>::max();
             * Компилятор ограничивает объекты размером в половину адресного пространства.
             * Поэтому полученное число делим на 2.
             * Так же у нас есть указатель на голову(head_), количество элементов(size_)
             * и компаратор(comparator_) все вместе это - BinaryTree
             * Так же создается один служебный узел это - (tree_node)
             * Все это вычитаем и для получение максимального числа нужно
             * полученное число поделить на один узел (tree_node)
             * 
             * @return size_type - максимально возомжное количество элементов в дереве
             */
            size_type max_size() const noexcept {
                return (((std::numeric_limits<size_type>::max() / 2) - sizeof(BinaryTree) - sizeof(tree_node)) / sizeof(tree_node));
            }

            /**
             * @brief Функция вставляет значения в узел, а затем в древо
             * 
             * @return iterator - iterator указывает на вставленный элемент
             */
            iterator insert(const Key& key) {
                tree_node* node = new tree_node(key);
                return this->insert(this->head_->parent_, node, false).first;
            }

            /**
             * @brief Функция втсавляет значения в узел только уникальные элементы,
             * а затем в древо.
             * @details если вставить не получилось, тогда созданный узел удаляем
             * 
             * @return pair<iterator, bool> - если получилось вставить элемент iterator
             * будет указывать на элемент который вставили и bool = true,
             * в противном случае iterator будет указывать на end() и bool = false
             */
            std::pair<iterator, bool> insertUnique(const Key& key) {
                tree_node* new_node = new tree_node(key);
                std::pair<iterator, bool> result = insert(this->head_->parent_, new_node, true);
                if (result.second == false) {
                    //Если не смогли вставить эелемент, надо его удалить
                    delete new_node;
                }
                return result;
            }

            /**
             * @brief Функция удаляет элемент с позиции
             * 
             */
            void erase(iterator pos) noexcept {
                delete this->extractNode(pos);
            }

            /**
             * @brief Находит элемент по ключу
             * @details В стандарте не регулируется какой именно элемент будет найден, если
             * их несколько, но в стандарте есть lower_bound,
             * поэтому делаем через lower_bound как в стандарте.
             * Если элемент не найден или больше key, тогда
             * возвращаем iterator указывающий на конец
             * 
             * @return iterator - будет указывать на найденный элемент, в противном
             * случае будет указывать на end()
             */
            iterator find(const_reference key) {
                iterator result = lowerBound(key);
                if (result == this->end() || this->comparator_(key, *result)) {
                    return this->end();
                }
                return result;
            }

            /**
             * @brief Аналогично функции find только для конст объекта
             * 
             */
            const_iterator find(const_reference key) const {
                const_iterator result = lowerBound(key);
                if (result == this->end() || this->comparator_(key, *result)) {
                    return this->end();
                }
                return result;
            }

            /**
             * @brief Функция вытаскивает все элементы из other, и вставляет их
             * в this.
             * @details Для экономия времени мы не будем копировать узлы, мы будем менять
             * только внутренние указатели узлов, т. к. нам не нужно проверять уникальность
             * узла
             */
            void merge(BinaryTree& other) {
                //Проверяем указатели что они не равны
                if (this != &other) {
                    iterator it_other = other.begin();
                    while (other.size_ > 0) {
                        // Сохраним во временную переменную чтоб отцепить его
                        // от других узлов
                        tree_node* temp = it_other.currentNode_;
                        // Сразу двигаем итератор, иначе после "отцепа" узлов
                        // мы не сможем перейти на след. узел
                        ++it_other;

                        // Нужно отцепить узел от других узлов
                        if (temp->parent_->left_ == temp) {
                            temp->parent_->left_ = nullptr;
                        }
                        if (temp->parent_->right_ == temp) {
                            temp->parent_->right_ = nullptr;
                        }
                        if (temp->right_ != nullptr) {
                            temp->right_->parent_ = temp->parent_;
                        }
                        if (temp->left_ != nullptr) {
                            temp->left_->parent_ = temp->parent_;
                        }

                        // Обнуляем указатели узла
                        temp->left_ = nullptr;
                        temp->right_ = nullptr;
                        temp->parent_ = nullptr;

                        // Узел нужно перекрасить в красный если он был черный,
                        // даже если он красный ничего страшного не будет
                        temp->color_ = Red;

                        // Теперь этот узел который отцепили вставляем в this
                        this->insert(this->head_->parent_, temp, false);

                        // Уменьшаем количество элементов(size_) в other
                        other.size_--;
                    }

                    // Приводим дерево other по умолчанию как при создании
                    other.head_->parent_ = nullptr;
                    other.head_->left_ = other.head_;
                    other.head_->right_ = other.head_;
                }

            }

            /**
             * @brief Функция вытаскивает только уникальные эелементы из other.
             * @details Все эелементы которые не вставились в this остаются в other, поэтому тут
             * придется потратить не много времени на изьятия узла использовав каждый раз
             * болансировку после изъятия
             */
            void mergeUnique(BinaryTree& other) {
                if (this != &other) {
                    iterator it_other = other.begin();
                    while (it_other != other.end()) {
                        // Проверяем есть ли такой элемент в this
                        if (this->find(it_other.currentNode_->key_) == this->end()) {
                            // Если он не нашел такого элемента, iterator будет указывать в конец
                            iterator temp = it_other;
                            ++it_other;
                            // Забираем узел из other и
                            // вставляем в this
                            tree_node* pick_up_node = other.extractNode(temp);
                            this->insert(this->head_->parent_, pick_up_node, false);
                        } else {
                            // Если нашли такой же узел, значит не трогаем его
                            // (оставляем его в other и переходим на следующий узел)
                            ++it_other;
                        }
                    }
                }
            }

            /**
             * @brief Функция находит элемент который >= key и возвращает iterator
             * указывающий на найденный элемент
             * 
             * @return iterator - указывает на найденный узел, в противном случае
             * указывает на end()
             */
            iterator lowerBound(const_reference key) noexcept {
                tree_node* result = this->head_;
                tree_node* begin = this->head_->parent_;

                while (begin != nullptr) {
                    if (this->comparator_(begin->key_, key)) {
                        // Если элемент меньше key значит идем в право,
                        // т.к. справа элементы больше
                        begin = begin->right_;
                    } else {
                        // Если элемент больше или равен key запоминаем его
                        result = begin;
                        // Так как элемент был больше или равен, идем влево
                        // т.к. слева распологаются элементы меньше текущего
                        begin = begin->left_;
                    }
                }
                
                return iterator(result);
            }

            /**
             * @brief Аналогично функции lowerBound только для конст объекта
             * 
             */
            const_iterator lowerBound(const_reference key) const noexcept {
                return const_cast<BinaryTree<Key, Comparator> *>(this)->lowerBound(key);
            }

            /**
             * @brief Функция находит элемент который больше key
             * 
             * @param key 
             * @return iterator 
             */
            iterator upperBound(const_reference key) noexcept {
                tree_node* result = this->head_;
                tree_node* begin = this->head_->parent_;
                while (begin != nullptr) {
                    if (this->comparator_(key, begin->key_)) {
                        // Если значение которое мы ищем меньше значения узла,
                        // то мы сохраняем этот узел
                        result = begin;
                        // Идем влево так как узел был больше искомого
                        begin = begin->left_;
                    } else {
                        // В другом случае идем в право
                        begin = begin->right_;
                    }
                }
                return iterator(result);
            }

            /**
             * @brief Аналогично функции upperBound только для конст объекта
             * 
             */
            const_iterator upperBound(const_reference key) const noexcept {
                return const_cast<BinaryTree<Key, Comparator> *>(this)->upperBound(key);
            }

            /**
             * @brief Вставляет новые элеметы в контейнер, если контейнер
             * не содержит таких ключей
             * 
             * @tparam Args 
             * @param args 
             * @return vector<std::pair<iterator,bool>> 
             */
            template<typename... Args>
            std::vector<std::pair<iterator,bool>> emplaceUnique(Args&&... args) {
                //Создаем вектор, что бы записать результат вставки всех элементов
                std::vector<std::pair<iterator, bool>> v;
                //Считаем количество аргументов и создаем память под вектор.
                //Это делается для того, чтоб каждый раз при вставке элемента
                //память не перевыделялась
                v.reserve(sizeof...(args));
                //Начинаем вставлять элементы
                for (auto element : {std::forward<Args>(args)...}) {
                    //Создаем объект который будем вставлять
                    tree_node* new_node = new tree_node(std::move(element));
                    //Вставляем элемент и записываем результат
                    std::pair<iterator, bool> result = this->insert(this->head_->parent_, new_node, true);
                    //Проверяем вставился элемент или нет
                    if (result.second == false) {
                        //Если элемент не вставился - надо его удалить
                        delete new_node;
                    }
                    v.push_back(result);
                }
                return v;
            }

            /**
             * @brief Аналогично emplaceUnique только вставляет все элементы
             * 
             * @tparam Args 
             * @param args 
             * @return vector<std::pair<iterator,bool>> 
             */
            template<typename... Args>
            std::vector<std::pair<iterator,bool>> emplace(Args&&... args) {
                //Создаем вектор, что бы записать результат вставки всех элементов
                std::vector<std::pair<iterator, bool>> v;
                //Считаем количество аргументов и создаем память под вектор.
                //Это делается для того, чтоб каждый раз при вставке элемента
                //память не перевыделялась
                v.reserve(sizeof...(args));
                //Начинаем вставлять элементы
                for (auto element : {std::forward<Args>(args)...}) {
                    //Создаем объект который будем вставлять
                    tree_node* new_node = new tree_node(std::move(element));
                    //Вставляем элемент и записываем результат
                    v.push_back(this->insert(this->head_->parent_, new_node, false));
                }
                return v;
            }


            /*----------------------------------------------------------------------------------*/

        private:

            /**
             * @brief Метод для копирования узлов начиная от copiedNode рекурсивно
             * 
             * @return tree_node* - возвращает новый копированный узел
             */
            tree_node* copyFromNode(tree_node* copiedNode, tree_node* parent) {
                tree_node* copy = new tree_node(copiedNode->key_, copiedNode->color_);
                if (copiedNode->left_ != nullptr) {
                    copy->left_ = copyFromNode(copiedNode->left_, copy);
                }

                if (copiedNode->right_ != nullptr) {
                    copy->right_ = copyFromNode(copiedNode->right_, copy);
                }
                copy->parent_ = parent;
                return copy;
            }

            /**
             * @brief Извлекает узел в позиции
             * @details процесс удаление BST, который гарантирует, что удаляемый узел является конечным узлом,
             * либо имеет только один дочерний узел.
             * @return tree_node* - извлеченный узел.
             */
            tree_node* extractNode(iterator pos) {
                tree_node* deleteNode = nullptr;
                // служебный узел нельзя удалять, запрещаем это делать
                if (pos != this->end()) {
                    deleteNode = pos.currentNode_;

                    // Обрабатываем стуацию, когда у deleteNode 2е детей
                    // (deleteNode может быть как красный так и черный)
                    if (deleteNode->right_ != nullptr && deleteNode->left_ != nullptr) {
                        // Ищем самый левый узел в правой ветке
                        tree_node* change = searchLeft(deleteNode->right_);
                        // Меняем их местами
                        swapNodes(deleteNode, change);
                    }

                    // Обрабатываем ситуацию когда deleteNode черный и
                    // у него есть 1 ребенок - он красный
                    if (deleteNode->color_ == Black &&
                        ((deleteNode->right_ == nullptr && deleteNode->left_ != nullptr) ||
                        (deleteNode->right_ != nullptr && deleteNode->left_ == nullptr))) {

                        //  где же наш красный узел, ищем...
                        tree_node* change;
                        if (deleteNode->right_ != nullptr) {
                            change = deleteNode->right_;
                        } else {
                            change = deleteNode->left_;
                        }

                        // Меняем местами найденный узел с узлом который удаляем
                        swapNodes(deleteNode, change);
                    }

                    // Обрабатываем ситуацию когда удаляемый узел черный без детей
                    // для этого нужно сбалансировать дерево так, чтобы после удаления
                    // черная высота не нарушилась
                    if (deleteNode->left_ == nullptr && deleteNode->right_ == nullptr &&
                        deleteNode->color_ == Black) {
                        balancingBeforeRemoval(deleteNode);
                    }

                    // Есть еще ситуация:
                    // Когда удаляемый узел красный без детей, мы просто его удаляем
                    // никаких действий не требуется

                    // Извлекаем узел из дерева
                    if (this->head_->parent_ == deleteNode) {
                        // Если узел deleteNode является корнем, значит он единственный
                        // элемент дерева, нам нужно служебный узел привести к изначальному
                        // состоянию
                        this->head_->left_ = this->head_;
                        this->head_->right_ = this->head_;
                        this->head_->parent_ = nullptr;
                    } else {
                        // Во всех других случаях отцепляем ссылки родителя
                        if (deleteNode->parent_->left_ == deleteNode) {
                            deleteNode->parent_->left_ = nullptr;
                        } else {
                            deleteNode->parent_->right_ = nullptr;
                        }

                        // Если удаляемый эелемент был самым большим
                        // ищем новый
                        if (this->head_->right_ == deleteNode) {
                            this->head_->right_ = searchRight(this->head_->parent_);
                        }

                        // Если удаляемый элемент был самым маленьким
                        // ищем новый
                        if (this->head_->left_ == deleteNode) {
                            this->head_->left_ = searchLeft(this->head_->parent_);
                        }
                    }

                    this->size_--;

                    // отцепляем ссылки удаляемого узла
                    deleteNode->left_ = nullptr;
                    deleteNode->right_ = nullptr;
                    deleteNode->parent_ = nullptr;
                }

                return deleteNode;
            }

            /**
             * @brief Функция балансировки перед удалением узла deleteNode,
             * @details нужна для того, что бы черная высота не нарушилась
             * Функция вызывается тогда, когда удаляется черный узел без детей
             * При балансировке возможны 8 случаев:
             * На самом деле их всего 4, остальные 4 отражают первые 4е
             * 
             * @param deleteNode 
             */
            void balancingBeforeRemoval(tree_node* deleteNode) {
                // checkNode - проверяемый элемент, для которого мы хотим востоновить черную высоту
                tree_node* checkNode = deleteNode;
                // parent - родитель
                tree_node* parent = deleteNode->parent_;

                // Проверка будет в цикле, так как из ситуации может возникнуть
                // потребность перейти на следующую итерации цикла для перехода к другой ситуации,
                // ну или пока дерево не кончится
                while (checkNode != this->head_->parent_ && checkNode->color_ == Black) {
                    if (checkNode == parent->left_) {
                        // Элемент checkNode находится слева от родителя
                        // sibling - второй ребенок parent
                        tree_node* sibling = parent->right_;

                        // Случай когда sibling красный.
                        // В этом случае мы меняем цвета sibling и parent, а затем делаем
                        // левый поворот через parent.
                        if (sibling->color_ == Red) {
                            std::swap(sibling->color_, parent->color_);
                            leftRotate(parent);
                            parent = checkNode->parent_;
                            sibling = parent->right_;
                        }

                        // Случай когда sibling черного цвета и его дети тоже черного цвета
                        // В таком случае меняем цвет sibling на красный
                        // и если цвет parent красный, меняем его на черный и в таком случае балансировка завершится.
                        // Если parent черный тогда идем балансировать parent - устанавливаем checkNode равной parent
                        // и переходим на след. итерацию цикла
                        if (sibling->color_ == Black &&
                            (sibling->left_ == nullptr || sibling->left_->color_ == Black) &&
                            (sibling->right_ == nullptr || sibling->right_->color_ == Black)) {
                            sibling->color_ = Red;
                            // проверяем что parent красный, и если да - меняем цвет и завершаем балансировку
                            if (parent->color_ == Red) {
                                parent->color_ = Black;
                                break;
                            }
                            // если нет, тогда балансируем parent
                            checkNode = parent;
                            parent = checkNode->parent_;
                        } else {
                            // Случай когда sibling черного цвета и его левый ребенок красный, а правый ребенок черный
                            // В этом случае меняем местами цвета sibiling и его левого ребенка, потом выполняем правый поворот через sibling
                            // Эти действия приводят к случаю ниже
                            if (sibling->left_ != nullptr && sibling->left_->color_ == Red &&
                                (sibling->right_ == nullptr || sibling->right_->color_ == Black)) {
                                std::swap(sibling->color_, sibling->left_->color_);
                                rightRotate(sibling);
                                sibling = parent->right_;
                            }

                            // Случай когда sibling черного цвета и его правый ребенок красный
                            // В таком случае мы меняем цвет правого ребенка на черный, меняем цвет
                            // sibling на цвет parent, меняем цвет parent на черный, потом выполняем левый поворот
                            // через sibling, после этого дерево будет сбалансировано
                            sibling->right_->color_ = Black;
                            sibling->color_ = parent->color_;
                            parent->color_ = Black;
                            leftRotate(parent);
                            break;
                        }

                    } else {
                        // Элемент checkNode находится справа от родителя
                        tree_node* sibling = parent->left_;

                        // Случай когда sibling красный.
                        // Отражает ситуацию выше
                        if (sibling->color_ == Red) {
                            std::swap(sibling->color_, parent->color_);
                            rightRotate(parent);
                            parent = checkNode->parent_;;
                            sibling = parent->left_;
                        }

                        // Случай когда sibling черного цвета и его дети тоже черного цвета
                        // Отражает ситуацию выше
                        if (sibling->color_ == Black &&
                            (sibling->left_ == nullptr || sibling->left_->color_ == Black) &&
                            (sibling->right_ == nullptr || sibling->right_->color_ == Black)) {
                            sibling->color_ = Red;
                            if (parent->color_ == Red) {
                                parent->color_ = Black;
                                break;
                            }
                            checkNode = parent;
                            parent = checkNode->parent_;
                        } else {
                            // Случай когда sibling черного цвета и его правый ребенок красный, а левый ребенок черный
                            // Отражает ситуацию выше
                            if (sibling->right_ != nullptr && sibling->right_->color_ == Red &&
                                (sibling->left_ == nullptr || sibling->left_->color_ == Black)) {
                                std::swap(sibling->color_, sibling->right_->color_);
                                leftRotate(sibling);
                                sibling = parent->left_;
                            }

                            // Случай когда sibling черного цвета и его левый ребенок красный
                            // Отражает ситуацию выше
                            sibling->left_->color_ = Black;
                            sibling->color_ = parent->color_;
                            parent->color_ = Black;
                            rightRotate(parent);
                            break;
                        }
                    }
                }
            }

            /**
             * @brief Меняем местами узлы deleteNode и other для удаления узла node.
             * Мы будем менять узлы целиком, а не данные (хотя это было бы удбнее), так как
             * оригинальная реализация дерева в STL требует от нас сохранять указатели и
             * итераторы валидными
             * 
             * @param deleteNode - элемент который хотим изъять
             * @param node - узел, который меняется местами с элементом, который изымается
             */
            void swapNodes(tree_node* deleteNode, tree_node* node) {
                // Меняем указатель на узел node у родителя node
                if (node->parent_->left_ == node) {
                    node->parent_->left_ = deleteNode;
                } else {
                    node->parent_->right_= deleteNode;
                }

                // Проверим, deleteNode является корнем дерева
                if (deleteNode == this->head_->parent_) {
                    this->head_->parent_ = node;
                } else {
                    // Меняем указатель на узел deleteNode у родтеля deleteNode
                    if (deleteNode->parent_->left_ == deleteNode) {
                        deleteNode->parent_->left_ = node;
                    } else {
                        deleteNode->parent_->right_ = node;
                    }
                }

                // Свапаем все кроме ключей, в описании написано, что будем менять узлы
                std::swap(deleteNode->left_, node->left_);
                std::swap(deleteNode->right_, node->right_);
                std::swap(deleteNode->color_, node->color_);
                std::swap(deleteNode->parent_, node->parent_);

                // Mеняем родителей у потомков
                if (node->left_ != nullptr) {
                    node->left_->parent_ = node;
                }

                if (node->right_ != nullptr) {
                    node->right_->parent_ = node;
                }

                if (deleteNode->left_ != nullptr) {
                    deleteNode->left_->parent_ = deleteNode;
                }

                if (deleteNode->right_ != nullptr) {
                    deleteNode->right_->parent_ = deleteNode;
                }
            }

            /**
             * @brief Находит среди потомков node самый левый элемент (малнький)
             * @return tree_node* возвращает найденный маленький элемент
             */
            tree_node* searchLeft(tree_node* node) noexcept {
                while (node->left_ != nullptr) {
                    node = node->left_;
                }
                return node;
            }

            /**
             * @brief Находит среди потомков node самый правый элемент (большой)
             * @return tree_node* возвращает найденный большой элемент
             */
            tree_node* searchRight(tree_node* node) noexcept {
                while (node->right_ != nullptr) {
                    node = node->right_;
                }
                return node;
            }


            /**
             * @brief Встраивает узел new_node в дерево ниже узла root.
             * 
             * @details функция может определять вставлять только уникальные или нет, для этого
             * передается флаг unique, если true - вставлять только уникальные узлы, если false - вставлять все узлы.
             */
            std::pair<iterator, bool> insert(tree_node* root, tree_node* new_node, bool unique) {
                tree_node* node = root;
                tree_node* parent = nullptr;

                // Ищем место для вставки. Нам нужно дойти до пустого узла...
                while (node != nullptr) {
                    parent = node;
                    if (this->comparator_(new_node->key_, node->key_)) {
                        node = node->left_;
                    } else {
                        // Проверка выключен ли флаг unique
                        if (unique == false) {
                            node = node->right_;
                        } else {
                            // Если флаг unique включен, тогда надо проверить ключ больше или равен
                            if (this->comparator_(node->key_, new_node->key_)) {
                                // Если new_node > тогда идем в правую сторону
                                node = node->right_;
                            } else {
                                // Если new_node == node возвращаем результат, что не можем вставить элемент
                                return {iterator(node), false};
                            }
                        }
                    }
                }

                // Вставляем узел, parent уже будет указывать на узел, new_node будет потомком для узла parent.
                // Parent так же может указывать и на nullptr, значит дерево пустое и new_node становится корнем дерева
                if (parent != nullptr) {
                    new_node->parent_ = parent;
                    // Проверяем в какую сторону кладем new_node
                    if (this->comparator_(new_node->key_, parent->key_)) {
                        parent->left_ = new_node;
                    } else {
                        parent->right_ = new_node;
                    }
                } else {
                    // Дерево пустое, значит new_node корень
                    new_node->color_ = Black;
                    new_node->parent_ = this->head_;
                    this->head_->parent_ = new_node;
                }
                this->size_++;

                // Надо обновить указатель на самый маленький и самый большой элемент
                if (this->head_->left_ == this->head_ || this->head_->left_->left_ != nullptr) {
                    this->head_->left_ = new_node;
                }
                if (this->head_->right_ == this->head_ || this->head_->right_->right_ != nullptr) {
                    this->head_->right_ = new_node;
                }

                // После того как мы вставили узел, нам нужно выполнить балансировку дерева
                balancingAfterInsertion(new_node);

                return {iterator(new_node), true};
            }



            /**
             * @brief Балансировка дерева после вставки нового эелемента
             * 
             * @details Не много расшифровки:
             * 1. node - добавленный элемент (сын), после вставки он нарушает правила (не всегда нарушает);
             * 2. parent - это папа элемента node;
             * 3. g_parent - это дедушка элемента node;
             * 4. uncle — дядя элемента node;
             * 
             * При балансировке возможны 6 различных случаев:
             * 1. 3 случая, когда дядя справа у деда
             * 2. 3 случая, когда дядя слева у деда
             * На самомом деле случая всего 3, остальные просто отражают первые 3 случая
             */
            void balancingAfterInsertion(tree_node* node) {
                tree_node* parent = node->parent_;
                // можно сделать рекурсией, но мы знаем что любую рекурсиию можно заменить цклом :)
                while (node != this->head_->parent_ && parent->color_ == Red) {
                    tree_node* g_parent = parent->parent_;
                    // Дядя справа у деда
                    if (g_parent->left_ == parent) {
                        tree_node* uncle = g_parent->right_;
                        if (uncle != nullptr && uncle->color_ == Red) {
                            // 1й случай:
                            // когда дядя и папа красный мы можем сделать "swap" цетов - перекрасить узлы дяди и папы на черный,
                            // а дед станет красным.

                            uncle->color_ = Black;
                            parent->color_ = Black;
                            g_parent->color_ = Red;

                            // Меняем указатели для следующего цикла
                            node = g_parent;
                            parent = node->parent_;
                        } else {
                            // 2й случай
                            // когда черный дядя - папа и дед в разных сторонах
                            if (parent->right_ == node) {
                                // Нам нужно превести к случаю, когда папа и дед идут в одну сторону,
                                // для этого нам нужно сделать левый поворот
                                leftRotate(parent);
                                // Нам нужно поменять указатели местами на отца и сына, так как мы сделали поворот
                                std::swap(parent, node);
                            }

                            // 3й случай
                            // когда черный дядя - папа и дед в одной стороне
                            // В этом случае нам нужно сделать так называемый большой поворот
                            // через деда к черному дяде и перекрасить отца в черный, а дедушку в красный
                            rightRotate(g_parent);
                            parent->color_ = Black;
                            g_parent->color_ = Red;
                            //После 2го или 3го случая нам нужно выйти из цикла
                            break;
                        }
                    } else {
                        // Дядя слева у деда
                        tree_node* uncle = g_parent->left_;
                        if (uncle != nullptr && uncle->color_ == Red) {
                            // 1й случай: аналогично ситуации, когда дядя справа у деда
                            uncle->color_ = Black;
                            parent->color_ = Black;
                            g_parent->color_ = Red;

                            node = g_parent;
                            parent = node->parent_;
                        } else {
                            // 2й случай: аналогично ситуации, когда дядя справа у деда
                            // отражение 2го случая
                            if (parent->left_ == node) {
                                rightRotate(parent);
                                std::swap(parent, node);
                            }
                            // 3й случай: аналогично ситуации, когда дядя справа у деда
                            // отражение 3го случая
                            leftRotate(g_parent);
                            parent->color_ = Black;
                            g_parent->color_ = Red;
                            break;
                        }
                    }
                }
                
                // Корень всегда останется черным после наших манипуляций
                this->head_->parent_->color_ = Black;
            }


            /**
             * @brief Делает левый поворот относительно node
             * 
             */
            void leftRotate(tree_node* node) noexcept {
                // Опорный элемент
                tree_node *pivotNode = node->right_;
                pivotNode->parent_ = node->parent_;

                if (this->head_->parent_ == node) {
                    this->head_->parent_ = pivotNode;
                } else if (node->parent_->left_ == node) {
                    node->parent_->left_ = pivotNode;
                } else {
                    node->parent_->right_ = pivotNode;
                }

                node->right_ = pivotNode->left_;

                if (pivotNode->left_ != nullptr) {
                    pivotNode->left_->parent_ = node;
                }

                node->parent_ = pivotNode;
                pivotNode->left_ = node;
            }

            /**
             * @brief Делает правый поворот относительно node
             *
             */
            void rightRotate(tree_node *node) noexcept {
                // Опорный элемент
                tree_node* pivotNode = node->left_;

                pivotNode->parent_ = node->parent_;

                if (this->head_->parent_ == node) {
                    this->head_->parent_ = pivotNode;
                } else if (node->parent_->left_ == node) {
                    node->parent_->left_ = pivotNode;
                } else {
                    node->parent_->right_ = pivotNode;
                }

                node->left_ = pivotNode->right_;
                if (pivotNode->right_ != nullptr) {
                    pivotNode->right_->parent_ = node;
                }

                node->parent_ = pivotNode;
                pivotNode->right_ = node;
            }

            // Удаляет узлы начиная от node рекурсивно
            void destroyNodes(tree_node* node) noexcept {
                // условие выхода из рекурсии
                if (node == nullptr) { return; }
                destroyNodes(node->left_);
                destroyNodes(node->right_);
                delete node;
            }

            /**
             * @brief Класс узла, который будет хранится в дереве
             * 
             */
            class BinaryTreeNode {
                public:
                    // Конструктор для создания головы дерева (head_)
                    BinaryTreeNode() : key_(Key{}) {
                        this->left_ = this;
                        this->right_ = this;
                        this->parent_ = nullptr;
                        this->color_ = Red;
                    }

                    // Конструктор для создания узла с значением
                    BinaryTreeNode(const Key& key) : key_(key) {
                        this->left_ = nullptr;
                        this->right_ = nullptr;
                        this->parent_ = nullptr;
                        this->color_ = Red;
                    }

                    // Конструктор для создания узла с значением и цветом
                    // В основном использую для копирования узлов
                    BinaryTreeNode(Key key, colorRB color) : key_(key) {
                        this->left_ = nullptr;
                        this->right_ = nullptr;
                        this->parent_ = nullptr;
                        this->color_ = color;
                    }

                    // Конструктор перемещения значения, чтоб не копировать просто так
                    // и не тратить время
                    BinaryTreeNode(Key&& key) : key_(std::move(key)){
                        this->left_ = nullptr;
                        this->right_ = nullptr;
                        this->parent_ = nullptr;
                        this->color_ = Red;
                    }

                    /**
                     * @brief функция возвращает iterator на следующий узел относитльно this
                     * @details у функции стоит const это делается для const_iterator, иначе компилятор будет ругаться,
                     * внутри функции мы отцепляем const
                     * 
                     */
                    tree_node* next() const noexcept{
                        tree_node* node = const_cast<tree_node*>(this);
                        // Проверяем, находимся ли мы в end?
                        // Если да тогда мы передвинем на самый маленький элемент
                        if (node->color_ == Red && (node->parent_ == nullptr || node->parent_->parent_ == node)) {
                            node = node->left_;
                        } else if (node->right_ != nullptr) {
                            // Если мы находимся не в end и если правая ветка не пустая, тогда идем на право
                            node = node->right_;

                            // и двигаемся в самый левый узел, это будет следующий элемент
                            while(node->left_ != nullptr) {
                                node = node->left_;
                            }
                        } else {
                            // В остальных случаях сдвигаемся к родителю до тех пор пока 
                            // node не окажется слева у родителя
                            tree_node* parent = node->parent_;
                            while(node == parent->right_) {
                                node = parent;
                                parent = parent->parent_;
                            }

                            // Проверка если наш parent оказался в end
                            // тогда передвигаем node в end
                            if (node->right_ != parent) {
                                node = parent;
                            }
                        }
                        return node;
                    }

                    /**
                     * @brief функция возвращает iterator на предыдущий узел относитльно this
                     * @details работает так же как и next(), только двигаемся в другую сторону
                     * (обратно)
                     */
                    tree_node* prev() const noexcept {
                        tree_node* node = const_cast<tree_node*>(this);
                        if (node->color_ == Red && (node->parent_ == nullptr || node->parent_->parent_ == node)) {
                            node = node->right_;
                        } else if (node->left_ != nullptr) {
                            node = node->left_;
                            while (node->right_ != nullptr) {
                                node = node->right_;
                            }
                        } else {
                            tree_node* parent = node->parent_;
                            while (node == parent->left_) {
                                node = parent;
                                parent = parent->parent_;
                            }

                            if (node->left_ != parent) {
                                node = parent;
                            }
                        }
                        return node;
                    }

                    tree_node* parent_;
                    tree_node* right_;
                    tree_node* left_;
                    colorRB color_;
                    Key key_;
            };

            /*-----------------------iterator-----------------------------*/

            /**
             * @brief Класс для итерации по элементам.
             * Сдесь представлены основные операторы для работы с итератором
             * 
             */
            class BinaryTreeIterator {
                friend BinaryTree;
                public:
                    // Пустой итератор нам не нужен - удаляем конструктор по умолчанию
                    BinaryTreeIterator() = delete;

                    reference operator*() {
                        return this->currentNode_->key_;
                    }

                    iterator &operator++() noexcept {
                        this->currentNode_ = this->currentNode_->next();
                        return *this;
                    }

                    iterator operator++(int) noexcept {
                        iterator temp(this->currentNode_);
                        ++(*this);
                        return temp;
                    }

                    iterator &operator--() noexcept {
                        this->currentNode_ = this->currentNode_->prev();
                        return *this;
                    }

                    iterator operator--(int) noexcept {
                        iterator temp(this->currentNode_);
                        --(*this);
                        return temp;
                    }

                    bool operator==(const iterator& other) const noexcept{
                        return this->currentNode_ == other.currentNode_;
                    }

                    bool operator!=(const iterator& other) const noexcept{
                        return this->currentNode_ != other.currentNode_;
                    }

                private:
                    BinaryTreeIterator(tree_node* node) {
                        this->currentNode_ = node;
                    }

                    tree_node* currentNode_;
            };
            
            /*--------------------------------------------------------------*/

            /*------------------------const_iterator------------------------*/

            /**
             * @brief Класс для итерации по элементам, но так как итератор констата
             * элемент нельзя будет изменить.
             * Сдесь представлены основные операторы для работы с итератором
             * 
             */
            class BinaryTreeConstIterator {
                friend BinaryTree;
                // Как дружественные, почему так - смотрите в s21::list::const_iterator
                friend bool operator==(const const_iterator& it1, const const_iterator& it2) noexcept {
                    return it1.currentNode_ == it2.currentNode_;
                }

                friend bool operator!=(const const_iterator& it1, const const_iterator& it2) noexcept {
                    return it1.currentNode_ != it2.currentNode_;
                }
                public:
                    // Пустой итератор нам не нужен - удаляем конструктор по умолчанию
                    BinaryTreeConstIterator() = delete;

                    BinaryTreeConstIterator(const iterator& other) {
                        this->currentNode_ = other.currentNode_;
                    }

                    const_reference operator*() const noexcept {
                        return this->currentNode_->key_;
                    }

                    const_iterator operator++() noexcept {
                        this->currentNode_ = this->currentNode_->next();
                        return *this;
                    }

                    const_iterator operator++(int) {
                        const_iterator temp(*this);
                        ++(*this);
                        return temp;
                    }

                    const_iterator operator--() noexcept {
                        this->currentNode_ = this->currentNode_->prev();
                        return *this;
                    }

                    const_iterator operator--(int) noexcept {
                        const_iterator temp(*this);
                        --(*this);
                        return temp;
                    }

                private:
                    const tree_node* currentNode_;
            };

            /*---------------------------------------------------------------*/
            // указатель на голову (служебный узел)
            tree_node* head_;
            // количество элементов в дереве
            size_type size_;
            // компоратор для сравнивания элементов
            // используем чтоб можно было в s21_map переопределить на наш компаратор
            // для сравнения ключей
            Comparator comparator_;
    }; // BinaryTree;
} // s21



#endif //SRC_S21_TREE_H_