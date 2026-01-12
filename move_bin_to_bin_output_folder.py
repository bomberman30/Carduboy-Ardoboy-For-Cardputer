import shutil
from os.path import join
import os

Import("env")

def after_build(source, target, env):
    # תיקיית build הנוכחית
    build_dir = env.subst("$BUILD_DIR")
    # הקובץ הבינארי שנוצר
    original_bin = join(build_dir, "firmware.bin")
    # תיקיית יעד חדשה (באותה תיקייה של הפרויקט)
    output_dir = join(env.subst("$PROJECT_DIR"), "bin_output")
    os.makedirs(output_dir, exist_ok=True)
    # שם חדש לקובץ
    new_bin = join(output_dir, env['PIOENV'] + ".bin")
    # העתקת הקובץ ושינוי שם
    shutil.copyfile(original_bin, new_bin)
    print("Copied", original_bin, "to", new_bin)

env.AddPostAction("buildprog", after_build)
