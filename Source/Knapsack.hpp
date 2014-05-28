#ifndef KNAPSACK_H
#define KNAPSACK_H


#include <exception>
#include <map>
#include <assert.h>


// Exception thrown when a knapsack item index is not found during a item lookup operation.
class KnapsackItemIndexNotFoundException: public std::exception {
    virtual const char* what() const throw() {
        return "Knapsack item index not found.";
    }
};


// A knapsack item.
template <typename ValueType, typename WeightType> class KnapsackItem {
private:

    int index;
    ValueType value;
    WeightType weight;

public:

    KnapsackItem(int index, ValueType value, WeightType weight) {
        this->index = index;
        this->value = value;
        this->weight = weight;
    }

    // Gets the item index.
    int getIndex() {
        return index;
    }

    // Sets the item index.
    void setIndex(int index) {
        this->index = index;
    }

    // Gets the item value.
    ValueType getValue() {
        return value;
    }

    // Sets the item value.
    void setValue(ValueType value) {
        this->value = value;
    }

    // Gets the item weight.
    WeightType getWeight() {
        return weight;
    }

    // Sets the item weight.
    void setWeight(WeightType weight) {
        this->weight = weight;
    }
};


// Represents a knapsack problem instance.
template <typename ValueType, typename WeightType> class KnapsackInstance {
private:

    std::map<int, KnapsackItem<ValueType,WeightType>*> items;
    WeightType capacity;

public:

    KnapsackInstance() {
    }

    // Destructor
    ~KnapsackInstance() {
        for (typename std::map<int, KnapsackItem<ValueType,WeightType>*>::iterator it = items.begin();
                it != items.end(); ++it)
        {
            delete it->second;
        }
    }

    // Gets the capacity of the knapsack.
    WeightType getCapacity() {
        return capacity;
    }

    // Sets the capacity of the knapsack.
    void setCapacity(WeightType capacity) {
        this->capacity = capacity;
    }

    // Gets a reference to the map of items. Items are indexed in this map by their indexes.
    std::map<int, KnapsackItem<ValueType,WeightType>*> const& getItems() {
        return items;
    }

    // Adds an item to this knapsack problem instance.
    void addItem(KnapsackItem<ValueType,WeightType>* item) {
        items.insert( std::pair<int, KnapsackItem<ValueType,WeightType>*>(item->getIndex(), item) );
    }

    // Adds an item to this knapsack problem instance.
    void addItem(int index, ValueType value, WeightType weight) {
        addItem(new KnapsackItem<ValueType,WeightType>(index, value, weight));
    }

    // Gets an item from this knapsack problem instance.
    KnapsackItem<ValueType,WeightType>* getItem(int index) {
        typename std::map<int, KnapsackItem<ValueType,WeightType>*>::iterator it;
        it = items.find(index);
        if (it == items.end())
            throw KnapsackItemIndexNotFoundException();
        else
            return it->second;
    }
};


// Represents a solution to a particular knapsack problem instance.
template <typename ValueType, typename AmountType> class KnapsackSolution {
private:

    std::map<int, AmountType> itemsAmounts;

    ValueType optimalValue;

public:

    // Gets the optimal value of the knapsack.
    ValueType getOptimalValue() {
        return optimalValue;
    }

    // Sets the optimal value >= 0 of the knapsack.
    void setOptimalValue(ValueType optimalValue) {
        assert(optimalValue >= 0);
        this->optimalValue = optimalValue;
    }

    // Adds the amount >= 0 that is allocated for an item in the knapsack.
    void addItemAmount(int itemIndex, AmountType amount) {
        assert(amount >= 0);
        this->itemsAmounts.insert( std::pair<int, AmountType>(itemIndex, amount) );
    }

    // Gets a reference to the map of allocated items amounts. Items are indexed in this map by their
    // indexes.
    std::map<int, AmountType> const& getItemsAmounts() {
        return itemsAmounts;
    }

    // Gets the amount allocated for a particular item in the knapsack.
    AmountType getItemAmount(int index) {
        typename std::map<int, AmountType>::iterator it;
        it = itemsAmounts.find(index);
        if (it == itemsAmounts.end())
            throw KnapsackItemIndexNotFoundException();
        else
            return it->second;
    }
};

#endif
