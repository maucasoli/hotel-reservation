#include "Main.h" // Your main form header file
#include "sqlite3.h" // Include SQLite header

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ args) {
    // Enable visual styles and set rendering compatibility
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Create and run the main form
    Hotel::Main form; // 'Hotel' is the project namespace; 'Main' is the form class
    Application::Run(% form);
}
