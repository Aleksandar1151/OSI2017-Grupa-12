# Javor - User Management and Authentication System

## Overview
Javor is a simple C++ console-based application designed for basic user authentication and role-based access management. 
It was developed as part of the **OSI2017 Group 12** project. The application supports user registration, login, and basic administrative operations.

The project implements:
- **User registration** with username, PIN, and role assignment.
- **User login** with credential verification.
- **Role-based menus** for administrators and analysts.
- **Persistent storage** of user credentials in a text file (`sifre.txt`).

## Features
### 1. User Registration
- Users can register by providing a unique username, a 4-digit PIN, and selecting a user group:
  - **Administrator** (group 1)
  - **Analyst** (group 2)
- Duplicate usernames are not allowed.
- Registration details are saved in `sifre.txt`.

### 2. User Login
- Users log in with a username and PIN.
- The application verifies credentials against stored data in `sifre.txt`.
- After successful login, the system loads a menu based on the user's role.

### 3. Administrator Menu
- **Change currency** (placeholder function).
- **Create a new account** (re-runs registration process).
- **Delete an account** (placeholder function).
- **Log out** (returns to login screen).
- **Exit** (closes the program).

### 4. Analyst Menu
- **Export data** (placeholder function).
- Automatically logs out after export.

### 5. Data Storage
- All users are stored in the `sifre.txt` file in the format:
  ```
  username PIN group
  ```
- Example:
  ```
  admin 1234 1
  analyst 5678 2
  ```

## File Structure
```
Javor/
│── Javor.sln               # Visual Studio solution file
│── Javor/                  # Project source code
│   ├── Functions.cpp       # Implementation of all core functions
│   ├── Functions.h         # Function declarations
│   ├── Source.cpp          # Entry point, runs login()
│   ├── sifre.txt           # Stored user credentials
│── Uputstvo.txt            # Project instructions
```

## How to Compile and Run
### Using Visual Studio
1. Open `Javor.sln` in Visual Studio.
2. Set the build configuration to **Debug** or **Release**.
3. Press **F5** to build and run.

### Using g++ (Command Line)
1. Navigate to the `Javor/Javor/` directory.
2. Compile the code:
   ```bash
   g++ Source.cpp Functions.cpp -o JavorApp
   ```
3. Run the program:
   ```bash
   ./JavorApp
   ```

## Example Usage
```
[Login]

Korisnicko ime:
> admin
Sifra:
> 1234

Na sistem je prijavljen [ admin ]

Opcije administratora:
    [ Promijenite valutu ]--------[ 1 ]
    [ Napravite novi nalog ]------[ 2 ]
    [ Obrisite nalog ]------------[ 3 ]
    [ Odjava ]--------------------[ 4 ]
    [ Izlaz ]---------------------[ 5 ]
>
```

## Limitations and Future Improvements
- Placeholder functions (`changeCurr()`, `deleteUser()`, `exportData()`) need full implementation.
- PINs are stored in plain text — encryption or hashing should be added.
- No input sanitization for special characters in usernames.

## License
This project is licensed under the MIT License.
