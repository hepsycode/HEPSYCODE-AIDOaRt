/**
 */
package org.univaq.hepsy;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;

import org.eclipse.emf.common.util.Enumerator;

/**
 * <!-- begin-user-doc -->
 * A representation of the literals of the enumeration '<em><b>Data Types</b></em>',
 * and utility methods for working with them.
 * <!-- end-user-doc -->
 * @see org.univaq.hepsy.HepsyPackage#getDataTypes()
 * @model
 * @generated
 */
public enum DataTypes implements Enumerator {
	/**
	 * The '<em><b>Int8 t</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #INT8_T_VALUE
	 * @generated
	 * @ordered
	 */
	INT8_T(0, "int8_t", "int8_t"),

	/**
	 * The '<em><b>Int16 t</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #INT16_T_VALUE
	 * @generated
	 * @ordered
	 */
	INT16_T(1, "int16_t", "sc_uint"),

	/**
	 * The '<em><b>Int32 t</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #INT32_T_VALUE
	 * @generated
	 * @ordered
	 */
	INT32_T(2, "int32_t", "int32_t"),

	/**
	 * The '<em><b>Int64 t</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #INT64_T_VALUE
	 * @generated
	 * @ordered
	 */
	INT64_T(3, "int64_t", "int64_t"),

	/**
	 * The '<em><b>Float</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #FLOAT_VALUE
	 * @generated
	 * @ordered
	 */
	FLOAT(4, "float", "float"),

	/**
	 * The '<em><b>Char</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #CHAR_VALUE
	 * @generated
	 * @ordered
	 */
	CHAR(5, "char", "char"),

	/**
	 * The '<em><b>String</b></em>' literal object.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #STRING_VALUE
	 * @generated
	 * @ordered
	 */
	STRING(6, "string", "string");

	/**
	 * The '<em><b>Int8 t</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #INT8_T
	 * @model name="int8_t"
	 * @generated
	 * @ordered
	 */
	public static final int INT8_T_VALUE = 0;

	/**
	 * The '<em><b>Int16 t</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #INT16_T
	 * @model name="int16_t" literal="sc_uint"
	 * @generated
	 * @ordered
	 */
	public static final int INT16_T_VALUE = 1;

	/**
	 * The '<em><b>Int32 t</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #INT32_T
	 * @model name="int32_t"
	 * @generated
	 * @ordered
	 */
	public static final int INT32_T_VALUE = 2;

	/**
	 * The '<em><b>Int64 t</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #INT64_T
	 * @model name="int64_t"
	 * @generated
	 * @ordered
	 */
	public static final int INT64_T_VALUE = 3;

	/**
	 * The '<em><b>Float</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #FLOAT
	 * @model name="float"
	 * @generated
	 * @ordered
	 */
	public static final int FLOAT_VALUE = 4;

	/**
	 * The '<em><b>Char</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #CHAR
	 * @model name="char"
	 * @generated
	 * @ordered
	 */
	public static final int CHAR_VALUE = 5;

	/**
	 * The '<em><b>String</b></em>' literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #STRING
	 * @model name="string"
	 * @generated
	 * @ordered
	 */
	public static final int STRING_VALUE = 6;

	/**
	 * An array of all the '<em><b>Data Types</b></em>' enumerators.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private static final DataTypes[] VALUES_ARRAY = new DataTypes[] { INT8_T, INT16_T, INT32_T, INT64_T, FLOAT, CHAR,
			STRING, };

	/**
	 * A public read-only list of all the '<em><b>Data Types</b></em>' enumerators.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public static final List<DataTypes> VALUES = Collections.unmodifiableList(Arrays.asList(VALUES_ARRAY));

	/**
	 * Returns the '<em><b>Data Types</b></em>' literal with the specified literal value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param literal the literal.
	 * @return the matching enumerator or <code>null</code>.
	 * @generated
	 */
	public static DataTypes get(String literal) {
		for (int i = 0; i < VALUES_ARRAY.length; ++i) {
			DataTypes result = VALUES_ARRAY[i];
			if (result.toString().equals(literal)) {
				return result;
			}
		}
		return null;
	}

	/**
	 * Returns the '<em><b>Data Types</b></em>' literal with the specified name.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param name the name.
	 * @return the matching enumerator or <code>null</code>.
	 * @generated
	 */
	public static DataTypes getByName(String name) {
		for (int i = 0; i < VALUES_ARRAY.length; ++i) {
			DataTypes result = VALUES_ARRAY[i];
			if (result.getName().equals(name)) {
				return result;
			}
		}
		return null;
	}

	/**
	 * Returns the '<em><b>Data Types</b></em>' literal with the specified integer value.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the integer value.
	 * @return the matching enumerator or <code>null</code>.
	 * @generated
	 */
	public static DataTypes get(int value) {
		switch (value) {
		case INT8_T_VALUE:
			return INT8_T;
		case INT16_T_VALUE:
			return INT16_T;
		case INT32_T_VALUE:
			return INT32_T;
		case INT64_T_VALUE:
			return INT64_T;
		case FLOAT_VALUE:
			return FLOAT;
		case CHAR_VALUE:
			return CHAR;
		case STRING_VALUE:
			return STRING;
		}
		return null;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private final int value;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private final String name;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private final String literal;

	/**
	 * Only this class can construct instances.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	private DataTypes(int value, String name, String literal) {
		this.value = value;
		this.name = name;
		this.literal = literal;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public int getValue() {
		return value;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public String getName() {
		return name;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public String getLiteral() {
		return literal;
	}

	/**
	 * Returns the literal value of the enumerator, which is its string representation.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public String toString() {
		return literal;
	}

} //DataTypes
