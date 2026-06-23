# Dungeon Quest — Lessons Learned

A running log of concepts practiced and real mistakes made (and fixed) while building Dungeon Quest in C++.

---

## Stage 1 — Fundamentals (Functions, Loops, Arrays)

**Functions**
- Default arguments go in the function **signature**, not the body.
  ```cpp
  void displayStats(string name, int health = 100, int attack = 10)
  ```
- Pass by reference (`&`) lets a function modify the *original* variable instead of a copy.
  ```cpp
  void damageTaken(int &health, int damage) { health -= damage; }
  ```

**Design thinking — "One job per function"**
- If I can't describe a function's job in **one sentence without using "and"**, it's doing too much.
- `main()` is the exception — it's allowed to be the *coordinator* that calls other functions.
- Real mistake I made: stuffed a whole combat loop + switch inside `damageTaken()`, when its only job should have been reducing health.

**Loops & control flow**
- `break` inside a `switch` only exits the `switch` — it does **not** exit an outer `while` loop.
- To exit a `while` loop from inside a `switch`, use a `bool` flag (e.g. `running = false`) and check it in the loop condition.
- A `break` sitting at the bottom of a `while` loop (outside the switch) will end the loop after just one iteration — easy mistake to make by accident.

**Arrays**
- Arrays are 0-indexed. Player-facing menus are usually 1-indexed (1, 2, 3...), so convert with `choice - 1` when accessing the array.
- Real bug I made: selected a monster from the array, but the combat loop kept using an old unrelated `monsterHealth` variable instead of the selected one. Lesson: after assigning a "selected" value, trace forward to make sure every later step actually uses it.

**Refactoring / Polish**
- Leftover test code (like a debug `damageTaken()` call from early testing) can silently cause confusing bugs later (e.g. hero starting combat with less than full health for no visible reason).
- Magic numbers (e.g. hardcoded `10` for damage) should become named variables (e.g. `monsterAttack`) for clarity and easy tuning.
- Redundant messages (printing the same outcome both inside a loop and after it) should be cleaned up — pick one place to announce results.

---

## Stage 2 — Pointers & Memory (Dynamic Inventory)

**Pointer basics**
- A pointer stores the **address** of a variable, not the value itself.
- Three symbols to remember:
  - `&` on a variable — "give me the address of this variable"
  - `*` in a declaration — "this variable is a pointer"
  - `*` in usage — "go to the address and get the value" (dereferencing)
- Real mistake I made: wrote `health -= damage` inside a pointer-based function — this modifies the pointer (the address) itself, not the value. Correct is `*health -= damage`.

**Pointer vs Pass by Reference**
- Both achieve the same result — modifying the original variable
- Pass by reference (`&`) is cleaner syntax and preferred for simple cases
- Pointers (`*`) are unavoidable for dynamic memory allocation
- Rule of thumb: use references when you can, pointers when you must

**Dynamic memory — `new` and `delete[]`**
- `new` allocates memory on the **heap** at runtime — size can be decided while the program runs
- `delete[]` frees that memory — forgetting this causes a **memory leak**
- Memory leak = allocating with `new` but never releasing with `delete[]` — memory stays occupied even when no longer needed
- Always use `delete[]` for arrays, `delete` for single values — mixing them causes undefined behavior

**Dynamic inventory expansion pattern**
- C++ arrays can't resize themselves — to "grow" one you must:
  1. Allocate a new bigger array (`new string[capacity + 1]`)
  2. Copy old items into it (loop)
  3. Add new item at the last slot (`newInventory[capacity] = newItem`)
  4. Free the old array (`delete[] inventory`)
  5. Point original pointer to new array (`inventory = newInventory`)
  6. Update capacity (`capacity++`)

**Pointer by reference — `string* &inventory`**
- Passing a pointer by reference (`*&`) lets a function modify where the pointer itself points to
- Without `&`, the function gets a copy of the pointer — changes to it don't affect `main()`'s pointer
- Real mistake I made: wrote `newInventory = inventory` (backwards) instead of `inventory = newInventory` — was pointing to deleted memory

---

*(Stage 3 notes will be added here after OOP & Classes.)*
