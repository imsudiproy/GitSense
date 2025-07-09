#include "git_branch_info.hpp"
#include <git2.h>
#include <iostream>

void print_branch_info(const std::string& repo_path) {
    git_libgit2_init();

    git_repository* repo = nullptr;
    if (git_repository_open(&repo, repo_path.c_str()) != 0) {
        std::cerr << "❌ Failed to open Git repository\n";
        git_libgit2_shutdown();
        return;
    }

    // Get HEAD reference
    git_reference* head = nullptr;
    if (git_repository_head(&head, repo) != 0) {
        std::cerr << "❌ Detached HEAD or no current branch\n";
        git_repository_free(repo);
        git_libgit2_shutdown();
        return;
    }

    const char* branch_name = nullptr;
    if (git_branch_name(&branch_name, head) != 0) {
        std::cerr << "❌ Could not get branch name\n";
        git_reference_free(head);
        git_repository_free(repo);
        git_libgit2_shutdown();
        return;
    }

    std::cout << "🔀 Current branch: " << branch_name << "\n";

    // Get tracking info
    git_reference* upstream = nullptr;
    if (git_branch_upstream(&upstream, head) == 0) {
        size_t ahead = 0, behind = 0;

        const git_oid* local_oid_ptr = git_reference_target(head);
        const git_oid* upstream_oid_ptr = git_reference_target(upstream);        
        if (!local_oid_ptr || !upstream_oid_ptr) {
            std::cout << "⚠️  Could not get reference targets for ahead/behind calculation.\n";
            git_reference_free(upstream);
            git_reference_free(head);
            git_repository_free(repo);
            git_libgit2_shutdown();
            return;
        }        
        git_oid local_oid = *local_oid_ptr;
        git_oid upstream_oid = *upstream_oid_ptr;


        if (git_graph_ahead_behind(&ahead, &behind, repo, &local_oid, &upstream_oid) == 0) {
            std::cout << "📡 Tracking status: "
                      << "ahead " << ahead << ", behind " << behind << "\n";
        } else {
            std::cout << "⚠️  Could not determine ahead/behind info.\n";
        }

        git_reference_free(upstream);
    } else {
        std::cout << "ℹ️ No upstream branch set.\n";
    }

    git_reference_free(head);
    git_repository_free(repo);
    git_libgit2_shutdown();
}

