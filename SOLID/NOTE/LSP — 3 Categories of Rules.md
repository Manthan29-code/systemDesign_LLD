# LSP — 3 Categories of Rules

### First Thought:
> **"A contract was signed by the parent. The child must honor it — not change the terms, not deliver less, not add hidden clauses."**

Think of it like a **franchise business** (McDonald's):
- The **parent** = McDonald's HQ (sets the rules)
- The **child** = Each franchise outlet (must follow those rules)
- The **customer** = The caller/client code

---

## Category 1 — Signature Rules
### First Thought:
> *"Does the child's method have the correct input/output shape?"*

**Real-life analogy:** McDonald's says every outlet must accept **cash and cards**. A franchise that only accepts cash — or starts accepting **crypto only** — breaks the contract.

---

### Sub-rule 1.1 — Contravariance of Parameters
> Child's method must accept the **same or broader** input types than parent.

```python
class Payment:
    def pay(self, amount: int):  # Parent accepts int
        pass

class ChildPayment(Payment):
    def pay(self, amount: float):  # ✅ Broader — accepts int too
        pass

class BadChildPayment(Payment):
    def pay(self, amount: PositiveInt):  # ❌ Narrower — rejects negatives
        pass                             # Strengthened precondition!
```

**Franchise analogy:** HQ says *"accept all customers"*. A franchise saying *"only VIP customers"* — violates the contract. ❌

---

### Sub-rule 1.2 — Covariance of Return Types
> Child's method must return the **same or narrower** type than parent.

```python
class Animal:
    def get_pet(self) -> Animal:   # Parent returns Animal
        pass

class DogShelter(Animal):
    def get_pet(self) -> Dog:      # ✅ Narrower — Dog IS-A Animal
        pass

class BadShelter(Animal):
    def get_pet(self) -> object:   # ❌ Broader — could return ANYTHING
        pass
```

**Franchise analogy:** HQ promises customers a *"burger"*. A franchise delivering a *"food item"* (could be anything!) — surprises the customer. ❌

---

### Sub-rule 1.3 — No New Exceptions
> Child must **not throw exceptions** the parent never declared.

```python
class FileReader:
    def read(self, path: str) -> str:
        return open(path).read()

class BadFileReader(FileReader):
    def read(self, path: str) -> str:
        raise NetworkException("File is on cloud!")  # ❌ Parent never warned about this!
```

**Franchise analogy:** HQ never said *"kitchen may explode"*. A franchise adding that risk breaks customer trust. ❌

---
---

## Category 2 — Property Rules
### First Thought:
> *"Does the child maintain the parent's core promises and behaviors over time?"*

**Real-life analogy:** McDonald's guarantees **consistent quality** across all outlets. If one outlet's burger tastes completely different every visit — the brand promise is broken.

---

### Sub-rule 2.1 — Invariant Preservation
> Properties that are **always true** in parent must remain always true in child.

```python
class BankAccount:
    def __init__(self):
        self.balance = 0  # INVARIANT: balance is always >= 0

    def withdraw(self, amount):
        if amount > self.balance:
            raise ValueError("Insufficient funds")
        self.balance -= amount

class BadChildAccount(BankAccount):
    def withdraw(self, amount):
        self.balance -= amount  # ❌ Balance can go NEGATIVE!
                                # Breaks the parent's core invariant
```

**Franchise analogy:** McDonald's rule — *"food must always be hygienic"*. A franchise serving unhygienic food breaks the non-negotiable standard. ❌

---

### Sub-rule 2.2 — History Constraint (State Rules)
> Child must **not allow state changes** the parent forbids.

```python
class ImmutablePoint:
    def __init__(self, x, y):
        self._x = x
        self._y = y
    # Parent is IMMUTABLE — coordinates never change after creation

class BadMutablePoint(ImmutablePoint):
    def move(self, x, y):
        self._x = x   # ❌ Parent promised immutability
        self._y = y   # Child secretly allows mutation — history broken!
```

**Franchise analogy:** McDonald's says *"the Big Mac recipe never changes"*. A franchise secretly swapping ingredients breaks the historical consistency customers rely on. ❌

---
---

## Category 3 — Method Rules
### First Thought:
> *"Does the child do at least what the parent promised — no more, no less?"*

**Real-life analogy:** McDonald's promises *"order ready in 3 minutes"*. A franchise taking 10 minutes **weakens** the promise. One delivering in 1 minute **strengthens** it — both acceptable? Only strengthening is. ✅

---

### Sub-rule 3.1 — Preconditions Cannot Be Strengthened
> Child cannot **demand more** from the caller than parent does.

```python
class Printer:
    def print_doc(self, doc: str):
        # Parent only checks: doc is not None
        if doc is None:
            raise ValueError()
        print(doc)

class BadPrinter(Printer):
    def print_doc(self, doc: str):
        if doc is None or len(doc) < 100:   # ❌ Now demanding doc be 100+ chars
            raise ValueError()              # Caller never expected this!
        print(doc)
```

**Franchise analogy:** HQ says *"serve anyone who walks in"*. A franchise saying *"only customers who pre-book"* — demands MORE from the customer. ❌

---

### Sub-rule 3.2 — Postconditions Cannot Be Weakened
> Child must **deliver at least what** the parent promised.

```python
class SortedList:
    def add(self, item):
        # Parent GUARANTEES: list is always sorted after add
        self._data.append(item)
        self._data.sort()  # ✅ Promise kept

class BadSortedList(SortedList):
    def add(self, item):
        self._data.append(item)  # ❌ No sorting! 
                                 # Parent promised sorted — child delivers unsorted
```

**Franchise analogy:** McDonald's promises *"fresh fries with every meal"*. A franchise giving day-old fries — delivers **less** than promised. ❌

---

## The Big Picture Summary

```
PARENT = A signed contract with the customer (caller)

┌─────────────────────────────────────────────────────────┐
│  SIGNATURE RULES     → Shape of the contract            │
│  • Params: accept same or broader       (contravariance) │
│  • Return: give same or narrower        (covariance)     │
│  • Exceptions: no new surprises                          │
├─────────────────────────────────────────────────────────┤
│  PROPERTY RULES      → Spirit of the contract           │
│  • Invariants: keep the core truths always               │
│  • History: don't secretly allow forbidden state changes │
├─────────────────────────────────────────────────────────┤
│  METHOD RULES        → Delivery of the contract         │
│  • Preconditions: don't ask MORE from caller             │
│  • Postconditions: don't give LESS than promised         │
└─────────────────────────────────────────────────────────┘

Child's golden rule:
"I can do MORE than parent — but NEVER LESS."
```