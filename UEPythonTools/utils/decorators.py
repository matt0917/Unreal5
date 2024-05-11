from functools import wraps

import unreal

def undoable(func=None, *, name="Action"):
    """
    Create an undo decorator with an optional name argument.
    This allows setting a custom name for the undo transaction.
    """
    if func is None:
        # If func is None, undoable has been called with parameters,
        # so we need to return a decorator that can take a function.
        return lambda func: undoable(func, name=name)

    @wraps(func)
    def wrapper(*args, **kwargs):
        # Start an undo transaction with the provided name
        with unreal.ScopedEditorTransaction(f'MP_UE_{name}'):
            try:
                result = func(*args, **kwargs)
                return result
            except Exception as e:
                unreal.log_error(f"An error occurred: {e}")
                raise
    return wrapper