import re
import difflib
from collections import defaultdict

import unreal

from .decorators import undoable


@undoable(name='Create Folder for Selected Actor')
def create_folder_for_selected_actors():
    create_folder_for_actors(get_selected_actors())
    unreal.log("Done: Created folders for the selected actors")

@undoable(name='Create Folder for all Actors')
def create_folder_for_all_actors():
    create_folder_for_actors(get_all_actors())
    unselect_all_actors()
    unreal.log("Done: Created folders for all actors")

@undoable(name='Unfold selected Actors')
def unfold_selected_actors_in_outliner():
    unfold_actors_in_outliner(get_selected_actors())
    unreal.log("Done: Unfold selected actors.")

@undoable(name='Unfold all Actors')
def unfold_all_actors_in_outliner():
    unfold_actors_in_outliner(get_all_actors())
    unreal.log("Done: Unfold all actors.")

def unfold_actors_in_outliner(all_actors):
    '''move all actors out of folders in the world outliner'''
    if not all_actors:
        return
    for actor in all_actors:
        actor.set_folder_path('/')
    unselect_all_actors()

def create_folder_for_actors(selected_actors=[]):
    if not selected_actors:
        unreal.log("No actors defined.")
    selected_actors_map = defaultdict(list)
    for actor in selected_actors:
        selected_actors_map[actor.get_actor_label()] = [actor, actor.get_folder_path()]
    # Check if there is at least one selected object
    if not selected_actors:
        unreal.log_warning("No objects selected.")
        return

    actor_strings = selected_actors_map.keys()

    grouped_strings = group_strings(actor_strings)
    for foldername, actor_labels in grouped_strings.items():
        # unreal.log(f"Group based on '{foldername}': {actor_labels}")
        for actor_label in actor_labels:
            actor = selected_actors_map[actor_label][0]
            actor_previous_folder = selected_actors_map[actor_label][1]
            actor.set_folder_path(f'{actor_previous_folder}/{foldername}')

    subsystem = unreal.EditorActorSubsystem(name='SelectActor_ACtorSubsystem')
    subsystem.set_selected_level_actors(selected_actors)




# Helper functions #################################################################
def get_similarity(s1, s2):
    """Calculate the similarity score between two strings."""
    return difflib.SequenceMatcher(None, s1, s2).ratio()


def get_selected_actors():
    return unreal.EditorActorSubsystem(
        name='SelectedActors_ActorSubSystem').get_selected_level_actors() or []


def get_all_actors():
    return unreal.EditorActorSubsystem(
        name='AllActors_ActorSubSystem').get_all_level_actors() or []


def unselect_all_actors():
    unreal.EditorActorSubsystem(name='ClearSelection_ActorSubSystem').select_nothing()


# Regular expression to remove trailing digits after any characters
def remove_trailing_digits(string):
    # This removes digits at the end of the string
    return re.sub(r'\d+$|[-_]?\d+$', '', string)


def group_strings(strings):
    """Group strings by similarity."""
    threshold = 0.6  # Define a similarity threshold
    groups = defaultdict(list)
    used = set()

    # Sort strings to improve clustering efficiency
    strings = sorted(strings, key=len)

    for i, base_string in enumerate(strings):
        if base_string in used:
            continue
        key_str = remove_trailing_digits(base_string) + '_GRP'
        if key_str in groups:
            key_str = f'{key_str}X'
        # Initialize the first group member
        groups[key_str].append(base_string)
        used.add(base_string)
        for comparison_string in strings[i+1:]:
            if comparison_string in used:
                continue
            # Calculate similarity and group them if they are similar enough
            if get_similarity(base_string, comparison_string) >= threshold:
                groups[key_str].append(comparison_string)
                used.add(comparison_string)
    return groups


def get_common_string_from_string_list(actor_list):
    # Regular expression to remove trailing digits after any characters
    def remove_trailing_digits(s):
        # This removes digits at the end of the string
        return re.sub(r'\d+$|[-_]?\d+$', '', s)

    strings = [remove_trailing_digits(actor.get_actor_label())
               for actor in actor_list]
    # Function to compare all strings to find the common prefix

    def common_prefix(strings):
        if not strings:
            return ""
        # Sort the list and compare the first and last items,
        # the ones that differ the most
        sorted_strings = sorted(strings)
        first, last = sorted_strings[0], sorted_strings[-1]
        for i, char in enumerate(first):
            if i >= len(last) or char != last[i]:
                return first[:i]
        return first

    # Find the common prefix among the first parts
    return common_prefix(strings)
