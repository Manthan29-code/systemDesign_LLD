

# 🧠 I — Interface Segregation Principle (ISP)

> **“Clients should not be forced to depend on methods they do not use.”**

---

## 🔍 First-Principles Thinking

### Step 1: Why do we create interfaces?

* To define a **contract**
* To ensure **consistent behavior**
* To enable **flexibility & abstraction**

---

### Step 2: What goes wrong?

Sometimes we create **fat interfaces**:

```cpp
// Too many unrelated responsibilities
```

👉 Classes are forced to implement methods they **don’t need**

---

## ❌ Violation Example (Fat Interface)

```cpp id="z7x0c1"
class Worker {
public:
    virtual void work() = 0;
    virtual void eat() = 0;
    virtual void sleep() = 0;
};
```

---

### Now implement:

```cpp id="nq9h5t"
class HumanWorker : public Worker {
public:
    void work() override { cout << "Human working\n"; }
    void eat() override { cout << "Human eating\n"; }
    void sleep() override { cout << "Human sleeping\n"; }
};

class RobotWorker : public Worker {
public:
    void work() override { cout << "Robot working\n"; }

    void eat() override {
        throw logic_error("Robot doesn't eat");
    }

    void sleep() override {
        throw logic_error("Robot doesn't sleep");
    }
};
```

---

## 🚨 Problems in This Code

### 1. ❌ Forced implementation

Robot must implement:

```cpp
eat()
sleep()
```

👉 Even though it **doesn’t need them**

---

### 2. 💣 Runtime errors

```cpp
throw logic_error("Robot doesn't eat");
```

👉 This is a **design failure**, not a runtime problem

---

### 3. ❌ Violates LSP too

* You promised all `Worker` can `eat()`
* Robot breaks that promise

---

### 4. ❌ Fragile design

If you add:

```cpp
virtual void takeBreak() = 0;
```

👉 All classes break

---

## 🧠 Core Problem

> Interface is **too general and bloated**

---

# ✅ Correct Design (Follow ISP)

## Step 1: Split Interfaces

```cpp id="qk8w2p"
class Workable {
public:
    virtual void work() = 0;
};

class Eatable {
public:
    virtual void eat() = 0;
};

class Sleepable {
public:
    virtual void sleep() = 0;
};
```

---

## Step 2: Implement only what is needed

```cpp id="c1m8zp"
class HumanWorker : public Workable, public Eatable, public Sleepable {
public:
    void work() override { cout << "Human working\n"; }
    void eat() override { cout << "Human eating\n"; }
    void sleep() override { cout << "Human sleeping\n"; }
};

class RobotWorker : public Workable {
public:
    void work() override { cout << "Robot working\n"; }
};
```

---

## 🔥 Usage

```cpp id="7zt2ax"
void manageWork(Workable* w) {
    w->work();
}
```

👉 No unnecessary dependency
👉 No fake implementations

---

# ⚖️ Violation vs Follow

| Aspect         | ❌ Violation | ✅ Follow ISP    |
| -------------- | ----------- | --------------- |
| Interface size | Large       | Small & focused |
| Forced methods | Yes         | No              |
| Runtime errors | Possible    | Avoided         |
| Flexibility    | Low         | High            |

---

# 🧩 Real-Life Analogy

### ❌ Violation

Imagine a **multi-tool remote**:

* Every device must support:

  * TV controls
  * AC controls
  * Washing machine controls

👉 Even if device doesn’t need it

---

### ✅ ISP Followed

Separate remotes:

* TV remote
* AC remote
* Washing machine remote

👉 Each device only implements what it needs

---

# 🌍 Real-World Example

### ❌ Bad API Design

```cpp
class UserService {
    login();
    uploadVideo();
    processPayment();
}
```

👉 Every client depends on everything

---

### ✅ Good Design

```cpp
class AuthService { login(); }
class VideoService { uploadVideo(); }
class PaymentService { processPayment(); }
```

👉 Clean separation

---

# 🚀 Benefits of Following ISP

* ✅ No unnecessary dependencies
* ✅ Cleaner code
* ✅ Easier testing
* ✅ Better maintainability
* ✅ Avoids fake implementations

---

# 🧠 Deep Insight

> ISP is about **keeping contracts minimal and meaningful**

---

# ⚠️ When NOT to Over-Split

* Too many tiny interfaces → complexity
* Balance is key

---

# 🧭 Mentor Advice

Whenever you design an interface, ask:

> “Will every implementation use ALL methods?”

If NO → split it

---

# 🧠 One-Line Summary

> **Don’t force a class to implement what it doesn’t need.**

---

## 🔁 Connection with Other SOLID Principles

* ISP helps **LSP** (no broken behavior)
* ISP helps **OCP** (easier extension)

---

