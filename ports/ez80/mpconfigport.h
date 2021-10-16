#include <stdint.h>
#include <alloca.h>

#define MICROPY_OBJ_REPR                    (MICROPY_OBJ_REPR_B)
#define MICROPY_GC_STACK_ENTRY_TYPE         uint24_t
#define MICROPY_ALLOC_PATH_MAX              (128)
#define MICROPY_ALLOC_LEXER_INDENT_INIT     (8)
#define MICROPY_ALLOC_PARSE_RULE_INIT       (48)
#define MICROPY_ALLOC_PARSE_RULE_INC        (8)
#define MICROPY_ALLOC_PARSE_RESULT_INC      (8)
#define MICROPY_ALLOC_PARSE_CHUNK_INIT      (16)
#define MICROPY_MEM_STATS                   (0)

#define MICROPY_CONFIG_ROM_LEVEL            (MICROPY_CONFIG_ROM_LEVEL_MINIMUM)

#define MICROPY_ENABLE_COMPILER             (1)

#define MICROPY_QSTR_EXTRA_POOL             mp_qstr_frozen_const_pool
#define MICROPY_ENABLE_GC                   (1)
#define MICROPY_HELPER_REPL                 (1)
#define MICROPY_MODULE_FROZEN_MPY           (1)
#define MICROPY_ENABLE_EXTERNAL_IMPORT      (1)
#define MICROPY_PY_MATH                     (1)
#define MICROPY_USE_INTERNAL_ERRNO          (1)

#define MICROPY_COMP_CONST_FOLDING          (1)
#define MICROPY_COMP_CONST_LITERAL          (1)
#define MICROPY_FULL_CHECKS                 (1)
#define MICROPY_MULTIPLE_INHERITANCE        (1)
#define MICROPY_PY_GENERATOR_PEND_THROW     (1)
#define MICROPY_PY_BUILTINS_RANGE_ATTRS     (1)

typedef intptr_t mp_int_t;
typedef uintptr_t mp_uint_t;
typedef long mp_off_t;

#define MICROPY_PORT_BUILTINS \
    { MP_ROM_QSTR(MP_QSTR_open), MP_ROM_PTR(&mp_builtin_open_obj) },

#define MICROPY_HW_BOARD_NAME "minimal"
#define MICROPY_HW_MCU_NAME "ez80-cpu"

#define MP_STATE_PORT MP_STATE_VM

#define MICROPY_PORT_ROOT_POINTERS \
    const char *readline_hist[8];
