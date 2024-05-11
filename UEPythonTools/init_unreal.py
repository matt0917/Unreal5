from importlib import reload
import unreal

from utils import asset_utils
reload(asset_utils)


class CustomToolMenu:
    '''Custom tool menu creating class'''
    MENU_NAME = 'MPTools_PyMenu'
    MENU_LABEL = 'MPTools'
    @classmethod
    def add_menu_item(cls):
        # Get the ToolMenus singleton
        tool_menus = unreal.ToolMenus.get()

        # Find or create the 'Python' menu in the main menu bar
        main_menu = tool_menus.find_menu("LevelEditor.MainMenu")
        if not main_menu:
            unreal.log_error("Main menu not found")
            return

        # Find or create the 'Python' section
        python_menu = main_menu.add_sub_menu(
            "Python", section_name="CustomScripts", name="MPTools_TMenu", label="MPTools")
        if not python_menu:
            unreal.log_error("Failed to find or create Python menu section")
            return

        fold_actors_menu_entry = cls.create_folder_for_all_actors_entry()
        unfold_actors_menu_entry = cls.unfold_all_actors_entry()
        fold_selected_actors_menu_entry = cls.create_folder_for_selected_actors_entry()

        python_menu.add_menu_entry("CustomScripts", fold_actors_menu_entry)
        python_menu.add_menu_entry("CustomScripts", unfold_actors_menu_entry)
        python_menu.add_menu_entry("CustomScripts", fold_selected_actors_menu_entry)

        # Refresh all widgets to update the menu
        tool_menus.refresh_all_widgets()

    @classmethod
    def create_folder_for_all_actors_entry(cls):
        # Define the menu entry
        menu_entry = unreal.ToolMenuEntry(
            name="CreateFolderForAllActors_func",
            owner=unreal.ToolMenuOwner("Python"),
            insert_position=unreal.ToolMenuInsert(
                position=unreal.ToolMenuInsertType.FIRST),
            type=unreal.MultiBlockType.MENU_ENTRY
        )
        menu_entry.set_label("Create folder for all Actors")
        menu_entry.set_tool_tip("Create folder for all Actors in the Outliner.")
        # Set the command to execute the Python function
        menu_entry.set_string_command(
            type=unreal.ToolMenuStringCommandType.PYTHON,
            custom_type="",
            string="asset_utils.create_folder_for_all_actors()"
        )
        return menu_entry

    @classmethod
    def unfold_all_actors_entry(cls):
        # Define the menu entry
        menu_entry = unreal.ToolMenuEntry(
            name="UnforldActor_func",
            owner=unreal.ToolMenuOwner("Python"),
            insert_position=unreal.ToolMenuInsert(
                position=unreal.ToolMenuInsertType.FIRST),
            type=unreal.MultiBlockType.MENU_ENTRY
        )
        menu_entry.set_label("Unfold all Actors in the Outliner")
        menu_entry.set_tool_tip("Unfold all actors in the outliner.")
        # Set the command to execute the Python function
        menu_entry.set_string_command(
            type=unreal.ToolMenuStringCommandType.PYTHON,
            custom_type="",
            string="asset_utils.unfold_actors_in_outliner()"
        )
        return menu_entry

    @classmethod
    def create_folder_for_selected_actors_entry(cls):
        # Define the menu entry
        menu_entry = unreal.ToolMenuEntry(
            name="CreateFolderForSelectedActor_func",
            owner=unreal.ToolMenuOwner("Python"),
            insert_position=unreal.ToolMenuInsert(
                position=unreal.ToolMenuInsertType.FIRST),
            type=unreal.MultiBlockType.MENU_ENTRY
        )
        menu_entry.set_label("Create folder for selected Actor(s)")
        menu_entry.set_tool_tip("Create folder for the selected Actor(s) in the Outliner.")
        # Set the command to execute the Python function
        menu_entry.set_string_command(
            type=unreal.ToolMenuStringCommandType.PYTHON,
            custom_type="",
            string="asset_utils.create_folder_for_selected_actors()"
        )
        return menu_entry


CustomToolMenu.add_menu_item()
