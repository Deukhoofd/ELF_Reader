#ifndef ELF_EXPORTER_TAGTYPE_HPP
#define ELF_EXPORTER_TAGTYPE_HPP

#include <cstdint>
#include <stdexcept>
#include <string>
#include <Arbutils/Enum.hpp>

ENUM(TagType, uint8_t,
     DW_TAG_compile_unit,
     DW_TAG_structure_type,
     DW_TAG_union_type,
     DW_TAG_enumeration_type,
     DW_TAG_typedef,
     DW_TAG_array_type,
     DW_TAG_subrange_type,
     DW_TAG_inheritance,
     DW_TAG_member,
     DW_TAG_subprogram,
     DW_TAG_formal_parameter,
     DW_TAG_namespace,
     DW_TAG_enumerator,
     DW_TAG_class_type,
     DW_TAG_base_type,
     DW_TAG_pointer_type,
     DW_TAG_const_type,
     DW_TAG_reference_type,
     DW_TAG_template_type_param,
     DW_TAG_template_value_param,
     DW_TAG_GNU_template_parameter_pack,
     DW_TAG_imported_declaration,
     DW_TAG_unspecified_type,
     DW_TAG_rvalue_reference_type,
     DW_TAG_restrict_type,
     DW_TAG_imported_module,
     DW_TAG_unspecified_parameters,
     DW_TAG_subroutine_type,
     DW_TAG_variable,
     DW_TAG_lexical_block,
     DW_TAG_ptr_to_member_type,
     DW_TAG_volatile_type,
     DW_TAG_inlined_subroutine
)
#endif // ELF_EXPORTER_TAGTYPE_HPP
