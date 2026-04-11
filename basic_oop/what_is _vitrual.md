<head></head>

Welcome back to the world of C++! Using the `virtual` keyword is essentially how we unlock **Runtime Polymorphism**. Since you've seen this before, let’s skip the fluff and dive straight into the mechanics, use cases, and the "gotchas" that often trip up developers.

* * *

## 1. Core Properties of the `virtual` Keyword

The `virtual` keyword tells the compiler to perform **Dynamic Binding** (or late binding). Instead of deciding which function to call at compile-time based on the *pointer type*, the program decides at runtime based on the *actual object type*.

- **VTable (Virtual Table):** For every class with virtual functions, the compiler creates a static table containing addresses of the virtual functions.
- **VPTR (Virtual Pointer):** Every object of that class contains a hidden pointer (vptr) that points to the VTable.
- **Inheritance:** Once a function is marked `virtual` in a base class, it remains `virtual` in all derived classes, even if you don't explicitly write the keyword again (though you should use `override`).

### Small Code Snippet

Using your `Car` example, let's look at how a standard virtual function differs from a pure virtual one:

```C++

class Car {
public:
    // Pure Virtual: Makes the class Abstract. Subclasses MUST implement this.
    virtual void startEngine() = 0; 

    // Regular Virtual: Provides a default behavior, but can be overridden.
    virtual void honk() {
        std::cout << "Beep beep!" << std::endl;
    }

    // Virtual Destructor: Essential for cleanup!
    virtual ~Car() {} 
};

class Tesla : public Car {
public:
    void startEngine() override {
        std::cout << "Silent start... system online." << std::endl;
    }
    // Tesla inherits the default honk() or can override it.
};

```

## 2. Practical Use Cases

| **Use Case** | **Description** |
| --- | --- |
| **Interface Design** | Creating an abstract base class (like your `Car`) to define a contract that all subclasses must follow. |
| **Heterogeneous Collections** | Storing different derived objects (e.g., `Tesla`, `Ford`, `Toyota`) in a single `std::vector<Car*>`. |
| **Framework Hooks** | Allowing users of a library to "plug in" their own logic by overriding specific virtual methods. |
| **Plugin Architectures** | Loading shared libraries at runtime where the main app only knows the interface, not the implementation. |

* * *

## 3. Mistakes to Avoid (The "Gotchas")

### 1. Forgetting the Virtual Destructor

This is the #1 C++ memory leak source. If you delete a derived object through a base pointer and the destructor isn't virtual, only the base part of the object is destroyed.

- **Fix:** Always make your destructor `virtual` in a base class.

### 2. Calling Virtual Functions in Constructors/Destructors

In C++, the object isn't "fully formed" as a derived type until the constructor finishes. If you call a virtual function in a `Car` constructor, it will call the `Car` version, **not** the `Tesla` version.

### 3. Object Slicing

If you pass a `Tesla` object **by value** into a function expecting a `Car`, the "Tesla parts" are stripped away (sliced).

- **Fix:** Always pass by **reference** (`Car&`) or **pointer** (`Car*`) to maintain polymorphism.

### 4. Overlooking the Performance Cost

Virtual functions have a tiny overhead (one extra pointer dereference). In 99% of apps, this doesn't matter, but in ultra-high-performance loops (like a physics engine), developers sometimes use "Curiously Recurring Template Pattern" (CRTP) to get polymorphism at compile-time instead.

* * *

## Summary Table

| **Feature** | **Virtual Function** | **Pure Virtual Function** |
| --- | --- | --- |
| **Syntax** | `virtual void func();` | `virtual void func() = 0;` |
| **Implementation** | Provided in Base. | Usually NOT provided in Base. |
| **Mandatory Override** | No. | Yes (unless child is also abstract). |
| **Class Status** | Concrete (can instantiate). | Abstract (cannot instantiate). |
