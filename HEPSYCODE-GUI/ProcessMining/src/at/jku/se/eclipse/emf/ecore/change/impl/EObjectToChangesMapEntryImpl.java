/**
 * Copyright (c) 2003-2006 IBM Corporation and others.
 * All rights reserved.   This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v20.html
 *
 * Contributors:
 *   IBM - Initial API and implementation
 */
package at.jku.se.eclipse.emf.ecore.change.impl;


import java.util.Collection;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.NotificationChain;
import org.eclipse.emf.common.util.BasicEMap;
import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.common.util.EMap;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.InternalEObject;
import org.eclipse.emf.ecore.impl.ENotificationImpl;
import org.eclipse.emf.ecore.impl.EObjectImpl;
import org.eclipse.emf.ecore.util.EObjectContainmentEList;
import org.eclipse.emf.ecore.util.InternalEList;

import at.jku.se.eclipse.emf.ecore.change.ChangePackage;
import at.jku.se.eclipse.emf.ecore.change.FeatureChange;


/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>EObject To Changes Map Entry</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link at.jku.se.eclipse.emf.ecore.change.impl.EObjectToChangesMapEntryImpl#getTypedKey <em>Key</em>}</li>
 *   <li>{@link at.jku.se.eclipse.emf.ecore.change.impl.EObjectToChangesMapEntryImpl#getTypedValue <em>Value</em>}</li>
 *   <li>{@link at.jku.se.eclipse.emf.ecore.change.impl.EObjectToChangesMapEntryImpl#getClassName <em>Class Name</em>}</li>
 * </ul>
 *
 * @generated
 */
public class EObjectToChangesMapEntryImpl extends EObjectImpl implements BasicEMap.Entry<EObject,EList<FeatureChange>>
{
  /**
   * The bit of {@link #eFlags} that is used to represent if key is a proxy.
   */
  protected static final int EPROXY_KEY = ELAST_EOBJECT_FLAG << 1;
  
  /**
	 * The cached value of the '{@link #getTypedKey() <em>Key</em>}' reference.
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @see #getTypedKey()
	 * @generated
	 * @ordered
	 */
  protected EObject key;

  /**
	 * The cached value of the '{@link #getTypedValue() <em>Value</em>}' containment reference list.
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @see #getTypedValue()
	 * @generated
	 * @ordered
	 */
  protected EList<FeatureChange> value;
  
  
  /**
	 * The default value of the '{@link #getClassName() <em>Class Name</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getClassName()
	 * @generated
	 * @ordered
	 */
	protected static final String CLASS_NAME_EDEFAULT = null;

		protected String className;
  

  /**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated
	 */
  protected EObjectToChangesMapEntryImpl()
  {
		super();
	}

  /**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated
	 */
  @Override
  protected EClass eStaticClass()
  {
		return ChangePackage.Literals.EOBJECT_TO_CHANGES_MAP_ENTRY;
	}

  /**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated
	 */
  public EObject getTypedKeyGen()
  {
		if (key != null && key.eIsProxy()) {
			InternalEObject oldKey = (InternalEObject)key;
			key = eResolveProxy(oldKey);
			if (key != oldKey) {
				if (eNotificationRequired())
					eNotify(new ENotificationImpl(this, Notification.RESOLVE, ChangePackage.EOBJECT_TO_CHANGES_MAP_ENTRY__KEY, oldKey, key));
			}
		}
		return key;
	}

  /**
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated NOT
   */
  public EObject getTypedKey()
  {
    if ((eFlags & EPROXY_KEY) != 0)
    {
      EObject newKey = getTypedKeyGen();
      if (!newKey.eIsProxy())
      {
        eFlags &= ~EPROXY_KEY;
      }
    }
    return key;
  }

  /**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated
	 */
  public EObject basicGetTypedKey()
  {
		return key;
	}

  /**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated NOT
	 */
  public void setTypedKeyGen(EObject newKey)
  {
		EObject oldKey = key;
		key = newKey;
		className = key.eClass().getName();
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, ChangePackage.EOBJECT_TO_CHANGES_MAP_ENTRY__KEY, oldKey, key));
	}

  /**
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated NOT
   */
  public void setTypedKey(EObject newKey)
  {
    setTypedKeyGen(newKey);
    if (key != null)
    {
      eFlags |= EPROXY_KEY;
    }
    else
    {
      eFlags &= ~EPROXY_KEY;
    }
  }

  /**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated
	 */
  public EList<FeatureChange> getTypedValue()
  {
		if (value == null) {
			value = new EObjectContainmentEList<FeatureChange>(FeatureChange.class, this, ChangePackage.EOBJECT_TO_CHANGES_MAP_ENTRY__VALUE);
		}
		return value;
	}

  /**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public String getClassName() {
		return className;
	}

		/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setClassName(String newClassName) {
		String oldClassName = className;
		className = newClassName;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, ChangePackage.EOBJECT_TO_CHANGES_MAP_ENTRY__CLASS_NAME, oldClassName, className));
	}

		/**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated
	 */
  @Override
  public NotificationChain eInverseRemove(InternalEObject otherEnd, int featureID, NotificationChain msgs)
  {
		switch (featureID) {
			case ChangePackage.EOBJECT_TO_CHANGES_MAP_ENTRY__VALUE:
				return ((InternalEList<?>)getTypedValue()).basicRemove(otherEnd, msgs);
		}
		return super.eInverseRemove(otherEnd, featureID, msgs);
	}

  /**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated
	 */
  @Override
  public Object eGet(int featureID, boolean resolve, boolean coreType)
  {
		switch (featureID) {
			case ChangePackage.EOBJECT_TO_CHANGES_MAP_ENTRY__KEY:
				if (resolve) return getTypedKey();
				return basicGetTypedKey();
			case ChangePackage.EOBJECT_TO_CHANGES_MAP_ENTRY__VALUE:
				return getTypedValue();
			case ChangePackage.EOBJECT_TO_CHANGES_MAP_ENTRY__CLASS_NAME:
				return getClassName();
		}
		return super.eGet(featureID, resolve, coreType);
	}

  /**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated
	 */
  @SuppressWarnings("unchecked")
  @Override
  public void eSet(int featureID, Object newValue)
  {
		switch (featureID) {
			case ChangePackage.EOBJECT_TO_CHANGES_MAP_ENTRY__KEY:
				setTypedKey((EObject)newValue);
				return;
			case ChangePackage.EOBJECT_TO_CHANGES_MAP_ENTRY__VALUE:
				getTypedValue().clear();
				getTypedValue().addAll((Collection<? extends FeatureChange>)newValue);
				return;
			case ChangePackage.EOBJECT_TO_CHANGES_MAP_ENTRY__CLASS_NAME:
				setClassName((String)newValue);
				return;
		}
		super.eSet(featureID, newValue);
	}

  /**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated
	 */
  @Override
  public void eUnset(int featureID)
  {
		switch (featureID) {
			case ChangePackage.EOBJECT_TO_CHANGES_MAP_ENTRY__KEY:
				setTypedKey((EObject)null);
				return;
			case ChangePackage.EOBJECT_TO_CHANGES_MAP_ENTRY__VALUE:
				getTypedValue().clear();
				return;
			case ChangePackage.EOBJECT_TO_CHANGES_MAP_ENTRY__CLASS_NAME:
				setClassName(CLASS_NAME_EDEFAULT);
				return;
		}
		super.eUnset(featureID);
	}

  /**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated
	 */
  @Override
  public boolean eIsSet(int featureID)
  {
		switch (featureID) {
			case ChangePackage.EOBJECT_TO_CHANGES_MAP_ENTRY__KEY:
				return key != null;
			case ChangePackage.EOBJECT_TO_CHANGES_MAP_ENTRY__VALUE:
				return value != null && !value.isEmpty();
			case ChangePackage.EOBJECT_TO_CHANGES_MAP_ENTRY__CLASS_NAME:
				return CLASS_NAME_EDEFAULT == null ? className != null : !CLASS_NAME_EDEFAULT.equals(className);
		}
		return super.eIsSet(featureID);
	}

  /**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public String toString() {
		if (eIsProxy()) return super.toString();

		StringBuilder result = new StringBuilder(super.toString());
		result.append(" (className: ");
		result.append(className);
		result.append(')');
		return result.toString();
	}

		/**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated
	 */
  protected int hash = -1;

  /**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated
	 */
  public int getHash()
  {
		if (hash == -1) {
			Object theKey = getKey();
			hash = (theKey == null ? 0 : theKey.hashCode());
		}
		return hash;
	}

  /**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated
	 */
  public void setHash(int hash)
  {
		this.hash = hash;
	}

  /**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated
	 */
  public EObject getKey()
  {
		return getTypedKey();
	}

  /**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated
	 */
  public void setKey(EObject key)
  {
		setTypedKey(key);
	}

  /**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated
	 */
  public EList<FeatureChange> getValue()
  {
		return getTypedValue();
	}

  /**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated
	 */
  public EList<FeatureChange> setValue(EList<FeatureChange> value)
  {
		EList<FeatureChange> oldValue = getValue();
		getTypedValue().clear();
		getTypedValue().addAll(value);
		return oldValue;
	}

  /**
	 * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
	 * @generated
	 */
  @SuppressWarnings("unchecked")
  public EMap<EObject, EList<FeatureChange>> getEMap()
  {
		EObject container = eContainer();
		return container == null ? null : (EMap<EObject, EList<FeatureChange>>)container.eGet(eContainmentFeature());
	}

} //EObjectToChangesMapEntryImpl
