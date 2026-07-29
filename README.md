# 🏦 Bank Client Management System (C++ Console App)

A console-based **Bank Management System** written in C++ that lets bank staff manage clients, handle transactions, and administer system users — all secured behind a login screen with **role-based permissions**. Data is persisted locally using flat text files, so no external database is required.

---

## ✨ Features

### 🔐 Authentication & Access Control
- 🔑 **Login screen** — users must authenticate with a username & password before accessing the system.
- 🛡️ **Permission-based access control** using bit-flags, so each user can be granted a custom combination of privileges (or **Full Access**):
  - 📋 View client list
  - ➕ Add new clients
  - ❌ Delete clients
  - ✏️ Update clients
  - 🔍 Find clients
  - 💰 Access transactions
  - 👥 Manage users
- 🚫 Users without permission are greeted with an **"Access Denied"** screen instead of the requested feature.

### 👤 Client Management
- 📃 **List all clients** in a neatly formatted table (account number, PIN, name, phone, balance).
- ➕ **Add new client(s)** with duplicate account-number checking, and the option to keep adding more in a loop.
- ❌ **Delete a client** by account number, with a confirmation prompt before removal.
- ✏️ **Update client info** (PIN, name, phone, balance) with confirmation before saving.
- 🔍 **Find a client** instantly by account number and view their full details.

### 💵 Transactions Menu
- 💰 **Deposit** funds into any client's account, with confirmation before the balance updates.
- 💸 **Withdraw** funds, with built-in validation to prevent withdrawing more than the available balance.
- 📊 **View total balances** — a summary table of every client's balance plus the grand total across the whole bank.

### 🧑‍💼 User Management (Admin Area)
- 📋 **List all system users** and their permission levels.
- ➕ **Add new users**, choosing between full access or a custom set of individual permissions.
- ❌ **Delete users** (password-protected confirmation).
- ✏️ **Update users** — change their permissions after re-verifying their password.
- 🔍 **Find a user** by username.

### 💾 Data Persistence
- 🗃️ Client records are stored in **`ClientsData.txt`**.
- 🗃️ User records are stored in **`UsersData.txt`**.
- 🔗 Each record is serialized using a custom delimiter (`#//#`) and parsed back into structured `sClient` / `stUser` objects on load — a lightweight, dependency-free alternative to a real database.
- 🧹 "Deleted" records are simply filtered out and the file is rewritten (soft-delete via a `MarkForDelete` flag).

### 🖥️ Navigation & UX
- 🧭 Clear, numbered menus for every screen (Main Menu, Transactions Menu, User Management Menu).
- 🔄 "Go back" prompts after every action, so the user always returns to the right menu.
- 🧼 Screen-clearing (`system("cls")`) between views for a cleaner console experience.

---

## 📸 Screenshots

### 🔐 Login Screen
Wrong credentials are caught immediately with a clear error message.

![Login Screen](Newfolder/Login.png)

### 🧭 Main Menu
The central hub for navigating to every feature in the system.

![Main Menu](screenshots/main-menu.png)

### 🔍 Find Client
Looking up a client instantly displays all their account details.

![Find Client Screen](screenshots/find-client.png)

### 💵 Transactions Menu
Deposit, withdraw, or check total balances across all clients.

![Transactions Menu](screenshots/transactions-menu.png)

### 👥 User Management
Admins can list, add, delete, update, and find system users from here.

![User Management Screen](screenshots/user-management.png)

### 🚫 Access Denied
Users without the right permission are blocked and told to contact their admin.

![Access Denied Screen](screenshots/access-denied.png)

---

## 🗂️ Project Structure

| Component | Description |
|---|---|
| `sClient` | Struct representing a bank client (account number, PIN, name, phone, balance, delete flag) |
| `stUser` | Struct representing a system user (username, password, permission bitmask, delete flag) |
| `enMainMenueOptions` | Enum for the main menu choices |
| `enTransactionOptions` | Enum for the transactions submenu |
| `enManageUserOptions` | Enum for the user-management submenu |
| `enPermissionMenue` | Bit-flag enum defining individual permissions |
| File I/O functions | `LoadClientDataFromFile`, `SaveClientDataToFile`, `LoadUserDataFromFile`, `SaveUserDataToFile`, `AddDataLineToFile` |
| Conversion helpers | `ConvertClientRecordToLine` / `ConvertLineToClientRecord`, `ConvertUserRecordToLine` / `ConvertLineToUserRecord` |

---

## 🔑 How Permissions Work

Permissions are stored as a single integer (bitmask) on each user record:

```
FullAccess          = -1   🌟 (overrides everything)
ShowClientListPer   = 1    📋
AddNewClientPer     = 2    ➕
DeleteCLientPer     = 4    ❌
UpdateClientPer     = 8    ✏️
FindClientPer       = 16   🔍
TransactionsMenuePer= 32   💰
ManageUsersPer      = 64   👥
```

When creating or updating a user, the admin answers a series of **Y/N** prompts, and the selected permissions are combined using bitwise OR (`|`). Access checks then use bitwise AND (`&`) to see if a required permission is present — unless the user has `FullAccess`, in which case everything is unlocked. 🔓

---

## ▶️ How to Run

1. 🛠️ Open the project in **Visual Studio** (uses `<conio.h>`, so it's built for Windows).
2. 🔨 Build and run the solution.
3. 🔐 Log in with a valid username & password from `UsersData.txt` (create this file with at least one user record if it doesn't exist yet).
4. 🧭 Navigate the menus using the numbered options shown on screen.

> ⚠️ **Note:** Since `<conio.h>` and `system("cls")/system("pause")` are Windows-specific, this project will need adaptation (e.g. replacing with cross-platform equivalents) to compile on Linux/macOS.

---

## 🚀 Possible Future Improvements

- 🖥️ Cross-platform support (remove Windows-only calls).
- 🗄️ Migrate from flat text files to a real database (SQLite, etc.).
- 🔒 Hash passwords instead of storing them in plain text.
- 🧪 Add input validation & unit tests.
- 🎨 Build a GUI or web front-end on top of the same logic.

---

## 📄 License

This project is open for learning and personal use. Feel free to fork it and build on top of it! 🙌
