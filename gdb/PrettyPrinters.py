import gdb

class StringSerializablePrinter:
    def __init__(self, val):
        self.val = val
    def to_string(self):
        try:
            return str(gdb.parse_and_eval(f"((StringSerializable*){int(self.val.address)})->toString()")) # jank?
        except Exception as ex:
            print("tostring", ex)
            return None

    def children(self):
        def recurse(val):
            t = val.type.strip_typedefs()
            if t.code == gdb.TYPE_CODE_PTR:
                val = val.dereference()
                t = val.type

            for f in t.fields():
                try:
                    if f.is_base_class:
                        base = val.cast(f.type)
                        yield from recurse(base)
                    elif not f.artificial: # artificial flavors
                        yield f.name, val[f.name]
                except Exception:
                    continue

        yield from recurse(self.val)

def derived(t, seen=None):
    if seen is None:
        seen = set()

    try:
        n = str(t.strip_typedefs())
    except Exception:
        return False

    if n in seen:
        return False

    seen.add(n)

    if n == "StringSerializable":
        return True

    try:
        for field in t.fields():
            if field.is_base_class and derived(field.type, seen):
                return True
    except Exception:
        pass

    return False

def build(val):
    try:
        if derived(val.type):
            return StringSerializablePrinter(val)
    except Exception:
        return None
    return None

gdb.pretty_printers.append(build)