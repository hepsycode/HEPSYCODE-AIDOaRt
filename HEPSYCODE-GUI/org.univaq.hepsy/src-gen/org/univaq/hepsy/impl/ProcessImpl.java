/**
 */
package org.univaq.hepsy.impl;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;
import org.eclipse.emf.ecore.impl.ENotificationImpl;
import org.univaq.hepsy.HepsyPackage;
import org.univaq.hepsy.Port;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Process</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link org.univaq.hepsy.impl.ProcessImpl#getProcessExtension <em>Process Extension</em>}</li>
 *   <li>{@link org.univaq.hepsy.impl.ProcessImpl#getPriority <em>Priority</em>}</li>
 *   <li>{@link org.univaq.hepsy.impl.ProcessImpl#getCriticality <em>Criticality</em>}</li>
 * </ul>
 *
 * @generated
 */
public class ProcessImpl extends NodeImpl implements org.univaq.hepsy.Process {
	/**
	 * The cached value of the '{@link #getProcessExtension() <em>Process Extension</em>}' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getProcessExtension()
	 * @generated
	 * @ordered
	 */
	protected Port processExtension;

	/**
	 * The default value of the '{@link #getPriority() <em>Priority</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getPriority()
	 * @generated
	 * @ordered
	 */
	protected static final int PRIORITY_EDEFAULT = 1;
	/**
	 * The cached value of the '{@link #getPriority() <em>Priority</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getPriority()
	 * @generated
	 * @ordered
	 */
	protected int priority = PRIORITY_EDEFAULT;

	/**
	 * The default value of the '{@link #getCriticality() <em>Criticality</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getCriticality()
	 * @generated
	 * @ordered
	 */
	protected static final int CRITICALITY_EDEFAULT = 0;

	/**
	 * The cached value of the '{@link #getCriticality() <em>Criticality</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getCriticality()
	 * @generated
	 * @ordered
	 */
	protected int criticality = CRITICALITY_EDEFAULT;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected ProcessImpl() {
		super();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected EClass eStaticClass() {
		return HepsyPackage.Literals.PROCESS;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Port getProcessExtension() {
		if (processExtension != null && processExtension.eIsProxy()) {
			InternalEObject oldProcessExtension = (InternalEObject) processExtension;
			processExtension = (Port) eResolveProxy(oldProcessExtension);
			if (processExtension != oldProcessExtension) {
				if (eNotificationRequired())
					eNotify(new ENotificationImpl(this, Notification.RESOLVE, HepsyPackage.PROCESS__PROCESS_EXTENSION,
							oldProcessExtension, processExtension));
			}
		}
		return processExtension;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public Port basicGetProcessExtension() {
		return processExtension;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setProcessExtension(Port newProcessExtension) {
		Port oldProcessExtension = processExtension;
		processExtension = newProcessExtension;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, HepsyPackage.PROCESS__PROCESS_EXTENSION,
					oldProcessExtension, processExtension));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public int getPriority() {
		return priority;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setPriority(int newPriority) {
		int oldPriority = priority;
		priority = newPriority;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, HepsyPackage.PROCESS__PRIORITY, oldPriority,
					priority));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public int getCriticality() {
		return criticality;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public void setCriticality(int newCriticality) {
		int oldCriticality = criticality;
		criticality = newCriticality;
		if (eNotificationRequired())
			eNotify(new ENotificationImpl(this, Notification.SET, HepsyPackage.PROCESS__CRITICALITY, oldCriticality,
					criticality));
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public Object eGet(int featureID, boolean resolve, boolean coreType) {
		switch (featureID) {
		case HepsyPackage.PROCESS__PROCESS_EXTENSION:
			if (resolve)
				return getProcessExtension();
			return basicGetProcessExtension();
		case HepsyPackage.PROCESS__PRIORITY:
			return getPriority();
		case HepsyPackage.PROCESS__CRITICALITY:
			return getCriticality();
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
	public void eSet(int featureID, Object newValue) {
		switch (featureID) {
		case HepsyPackage.PROCESS__PROCESS_EXTENSION:
			setProcessExtension((Port) newValue);
			return;
		case HepsyPackage.PROCESS__PRIORITY:
			setPriority((Integer) newValue);
			return;
		case HepsyPackage.PROCESS__CRITICALITY:
			setCriticality((Integer) newValue);
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
	public void eUnset(int featureID) {
		switch (featureID) {
		case HepsyPackage.PROCESS__PROCESS_EXTENSION:
			setProcessExtension((Port) null);
			return;
		case HepsyPackage.PROCESS__PRIORITY:
			setPriority(PRIORITY_EDEFAULT);
			return;
		case HepsyPackage.PROCESS__CRITICALITY:
			setCriticality(CRITICALITY_EDEFAULT);
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
	public boolean eIsSet(int featureID) {
		switch (featureID) {
		case HepsyPackage.PROCESS__PROCESS_EXTENSION:
			return processExtension != null;
		case HepsyPackage.PROCESS__PRIORITY:
			return priority != PRIORITY_EDEFAULT;
		case HepsyPackage.PROCESS__CRITICALITY:
			return criticality != CRITICALITY_EDEFAULT;
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
		if (eIsProxy())
			return super.toString();

		StringBuilder result = new StringBuilder(super.toString());
		result.append(" (priority: ");
		result.append(priority);
		result.append(", criticality: ");
		result.append(criticality);
		result.append(')');
		return result.toString();
	}

} //ProcessImpl
