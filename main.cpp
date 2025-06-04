#include <iostream>
#include <unistd.h>
#include <pwd.h>
#include <vector>
#include <sys/wait.h>
#include <readline/readline.h>   // keep for input editing
//#include <readline/history.h>  // removed for no history support
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <fcntl.h>
#include <map>
#include <ctime>

// ANSI colors (no neon background)
#define COLOR_RESET      "\033[0m"
#define COLOR_GREEN      "\033[1;32m"
#define COLOR_BLUE       "\033[1;34m"
#define COLOR_CYAN       "\033[1;36m"
#define COLOR_YELLOW     "\033[1;33m"
#define COLOR_MAGENTA    "\033[1;35m"
#define COLOR_RED        "\033[1;31m"

// Fun sentences for the prompt
const std::vector<std::string> funSentences = {
    "Ready to hack the planet! >",
    "Type 'help' if you get lost. >",
    "Shell yeah! 🚀 >",
    "What shall we do next? >",
    "Your wish is my command. >",
    "Let's get things done! >",
    "Stay curious, coder. >",
    "Adventure awaits >"
};

// Motivational quotes for 'motivate' command
const std::vector<std::string> motivationalQuotes = {
    "Keep pushing forward! 🚀",
    "Every bug is a lesson. 🐞",
    "You are the compiler of your destiny.",
    "Stay positive, work hard, make it happen.",
    "Eat, Sleep, Code, Repeat.",
    "Dream big, code bigger!",
    "You got this! 💪"
};

// Map common English phrases to shell commands
std::string englishToCommand(const std::string& input) {
    static const std::map<std::string, std::string> phraseMap = {
        {"list files", "ls"},
        {"show files", "ls"},
        {"show current directory", "pwd"},
        {"where am i", "pwd"},
        {"go home", "cd ~"},
        {"go up", "cd .."},
        {"clear screen", "clear"},
        {"show processes", "ps"},
        {"show help", "help"},
        {"exit shell", "exit"},
        {"quit", "exit"},
        {"motivate me", "motivate"},
        {"inspire me", "motivate"},
        {"what's the time", "time"},
        {"show time", "time"},
        // Removed history mappings here
    };
    auto it = phraseMap.find(input);
    if (it != phraseMap.end())
        return it->second;
    return input;
}

std::string getPrompt()
{
    static bool seeded = false;
    if (!seeded) { srand(time(nullptr)); seeded = true; }
    std::string fun = funSentences[rand() % funSentences.size()];

    std::ostringstream prompt;
    prompt << COLOR_MAGENTA << "Mr. Shell 😎" << COLOR_RESET << " > "
           << COLOR_CYAN << fun << COLOR_RESET << " ";
    return prompt.str();
}

std::vector<std::string> parseCommand(const std::string &line)
{
    std::istringstream iss(line);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token)
        tokens.push_back(token);
    return tokens;
}

void executeCommand(const std::vector<std::string> &args, bool background)
{
    if (args.empty())
        return;

    if (args[0] == "exit")
        exit(0);

    if (args[0] == "help")
    {
        std::cout << COLOR_CYAN << "Built-in commands:\n"
                  << "  cd [dir]    - change directory\n"
                  << "  exit        - exit shell\n"
                  << "  help        - show help\n"
                  << "  motivate    - get a motivational quote\n"
                  << "  time        - show current time\n"
                  << COLOR_RESET;
        return;
    }

    if (args[0] == "motivate")
    {
        std::string quote = motivationalQuotes[rand() % motivationalQuotes.size()];
        std::cout << COLOR_YELLOW << quote << COLOR_RESET << std::endl;
        return;
    }

    if (args[0] == "time")
    {
        time_t now = time(0);
        char* dt = ctime(&now);
        std::cout << COLOR_BLUE << "Current time: " << dt << COLOR_RESET;
        return;
    }

    if (args[0] == "cd")
    {
        const char *path = args.size() > 1 ? args[1].c_str() : getenv("HOME");
        if (chdir(path) != 0)
            perror("cd failed");
        return;
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        std::vector<char *> cargs;
        for (auto &arg : args)
            cargs.push_back(const_cast<char *>(arg.c_str()));
        cargs.push_back(nullptr);
        execvp(cargs[0], cargs.data());
        perror("exec failed");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        int status = 0;
        if (!background)
            waitpid(pid, &status, 0);
        if (!background) {
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
                std::cout << COLOR_GREEN << "✔" << COLOR_RESET << std::endl;
            else
                std::cout << COLOR_RED << "✘" << COLOR_RESET << std::endl;
        }
    }
    else
    {
        perror("fork failed");
    }
}

int main()
{
    // Removed using_history();

    std::cout << COLOR_GREEN
              << "  __  __          _____ _          _ _ \n"
              << " |  \\/  |       / ____| |        | | |\n"
              << " | \\  / |_ __  | (___ | |__   ___| | |\n"
              << " | |\\/| | '__   \\___ \\| '_ \\ / _ \\ | |\n"
              << " | |  | | |     ____) | | | |  __/ | |\n"
              << " |_|  |_|_|  || |_____/|_| |_|\\___|_|_|\n"
              << "          by adiicodes\n"
              << COLOR_RESET << std::endl;

    while (true)
    {
        std::string prompt = getPrompt();
        char *input = readline(prompt.c_str());
        if (!input)
            break;

        std::string line(input);
        free(input);

        if (line.empty())
            continue;

        // Removed add_history(line.c_str());

        bool background = false;
        if (!line.empty() && line.back() == '&')
        {
            background = true;
            line.pop_back();
        }

        line = englishToCommand(line);

        auto args = parseCommand(line);
        executeCommand(args, background);
    }

    std::cout << "\nExiting MyShell++...\n";
    return 0;
}
