#include "restaurant.h"


Restaurant::Restaurant() {
    name_ = "Restaurant";
    max_counter_space_ = 10;
    order_count_ = 0;
    total_order_count_ = 0;
    is_open_ = true;
    orders_front_ = NULL;
    orders_end_ = NULL;
}


Restaurant::Restaurant(std::string n, int max) {
    name_ = n;
    max_counter_space_ = max;
    order_count_ = 0;
    total_order_count_ = 0;
    is_open_ = true;
    orders_front_ = NULL;
    orders_end_ = NULL;
}


void Restaurant::open() {
    is_open_ = true;
}


void Restaurant::close() {
    is_open_ = false;
}


bool Restaurant::placeOrder(std::string n, std::string f) {
    // New orders go last
    if (isOpen() == false || total_order_count_ == max_counter_space_) {
      return false;
    }
    Order* new_order = new Order(n, f);
    if (orders_end_ == NULL) {
      orders_front_ = new_order;
    } else {
      orders_end_->setNextOrder(new_order);
    }
    orders_end_ = new_order;
    order_count_++;
    total_order_count_++;
    return true;
}


bool Restaurant::pickUpOrder() {
    if (isOpen() == false) {
      return false;
    }

    if (order_count_ > 0) {
        Order *curr_front = orders_front_;
        if (curr_front->isComplete()) {
            orders_front_ = orders_front_->getNextOrder();
            delete curr_front;
            order_count_--;
            total_order_count_--;
            return true;
        }
        return false;
    }
    return false;
}


bool Restaurant::completeOrder() {
    // Return true if order is ready for a customer, else false
    Order *incomplete_order = orders_front_;
    if (is_open_ == false || incomplete_order == NULL) {
      return false;
    }

    while (incomplete_order != NULL && incomplete_order->isComplete()) {
        incomplete_order = incomplete_order->getNextOrder();
    }

    if (incomplete_order != NULL) {
        return incomplete_order->completeOrder();
    } else {
        return false;
    }
}


void Restaurant::displayMenu() {
    std::cout << "The special of the day is: Poutine, eh!" << std::endl;
}


void Restaurant::printOrders() {
    Order *currOrder = orders_front_;
    for (int i = 0; i < order_count_; i++) {
        std::cout << "\nOrder #" << i << " : ";
        currOrder->printOrder();
    }

    std::cout << "\n--Total number of orders: " << order_count_ << std::endl;
}


bool Restaurant::isOpen() {
    return is_open_;
}

// Getters

int Restaurant::getMaxCounterSpace() {
    return max_counter_space_;
}


int Restaurant::getOrderCount() {
    return order_count_;
}


std::string Restaurant::getName() {
    return name_;
}

Order * Restaurant::getOrdersFront() {
  return orders_front_;
}



Restaurant::~Restaurant() {
  Order* curr_order = orders_front_;
  while (curr_order != NULL) {
      Order* temp = curr_order;
      curr_order = curr_order->getNextOrder();
      delete temp;
  }
}
