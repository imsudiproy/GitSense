#include "git_repo_checker.hpp"
#include <git2.h>
#include <iostream>

bool isGitRepository(const std::string& path) {
    git_libgit2_init();

    git_repository* repo = nullptr;
    int error = git_repository_open_ext(&repo, path.c_str(), 0, nullptr);

    if (error != 0) {
        const git_error* e = git_error_last();
        std::cerr << "❌ Not a Git repository: " << (e ? e->message : "Unknown error") << "\n";
        git_libgit2_shutdown();
        return false;
    }

    std::cout << "✅ Git repository detected at: " << path << "\n";

    git_repository_free(repo);
    git_libgit2_shutdown();
    return true;
}
