#include <hw_interface.hpp>

/// Recursively walks a directory tree and populates a hierarchical folder/file model.
///
/// Builds a tree of `_folder_` and `_file_` nodes starting at `path`.  
/// For each subdirectory, creates a `_folder_`, updates its `path`, recurses into it,
/// then appends it to `dir.elements`. For each regular file, creates a `_file_`,
/// sets its `path`, and appends it to `dir.elements`.
///
/// @note `f_path` is used as a mutable accumulator for the current path and is
///       modified in-place during recursion.
///       If you pass `f_path` by reference (as here), remember to restore it
///       after the recursive call to avoid path growth across siblings.
///       Consider passing `f_path` by value or using a local guard to restore it.
///
/// @param[out] dir     Destination node representing the current folder; will receive children.
/// @param[in]  path    Filesystem path to traverse (on disk).
void folders::walk_dir(_folder_& dir)
{
    for (const auto& i : fs::directory_iterator(dir.path))
    {
        if (i.is_directory())
        {
            _folder_ subfolder(i.path().filename().string());
            subfolder.path=dir.path+"/"+subfolder.name;
            walk_dir(subfolder);   
            dir.elements.push_back(subfolder);
        }
        else
        {
            _file_ new_file(i.path().filename().string());
            new_file.path=dir.path+"/"+new_file.name;
            dir.elements.push_back(new_file);
        }
    }
}

/// Returns the root folder model by scanning (or creating) the base directory.
///
/// Uses the current working directory as base and ensures a `root` subdirectory exists.
/// Builds a `_folder_` tree labeled "Projects" by walking `<cwd>/root`.
///
/// @return A fully-populated `_folder_` representing the project tree.
///
/// @note The on-disk directory is `<cwd>/root`, while the user-facing label is "Projects".
///       Adjust names if you want the label to mirror the physical directory name.
_folder_ folders::get_instances()
{
    auto base =std::filesystem::current_path().string();

    std::string directory = base+"/root";
    
    if (!fs::exists(directory) || !fs::is_directory(directory))
    {
        std::cerr << "Missing directory or wrong path, creating new.\n";
        fs::create_directory(directory);
    }
    _folder_ root("Projects");
    root.path = directory;
    walk_dir(root);
    return root;
}

