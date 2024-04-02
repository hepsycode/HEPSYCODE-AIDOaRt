/**
 */
package org.univaq.hepsy.impl;

import java.util.Collection;

import org.eclipse.emf.common.notify.NotificationChain;

import org.eclipse.emf.common.util.EList;

import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.InternalEObject;

import org.eclipse.emf.ecore.util.EObjectContainmentEList;
import org.eclipse.emf.ecore.util.InternalEList;

import org.univaq.hepsy.HepsyPackage;
import org.univaq.hepsy.StructuredNode;

/**
 * <!-- begin-user-doc -->
 * An implementation of the model object '<em><b>Structured Node</b></em>'.
 * <!-- end-user-doc -->
 * <p>
 * The following features are implemented:
 * </p>
 * <ul>
 *   <li>{@link org.univaq.hepsy.impl.StructuredNodeImpl#getProcesses <em>Processes</em>}</li>
 * </ul>
 *
 * @generated
 */
public class StructuredNodeImpl extends NodeImpl implements StructuredNode {
	/**
	 * The cached value of the '{@link #getProcesses() <em>Processes</em>}' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see #getProcesses()
	 * @generated
	 * @ordered
	 */
	protected EList<org.univaq.hepsy.Process> processes;

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	protected StructuredNodeImpl() {
		super();
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	protected EClass eStaticClass() {
		return HepsyPackage.Literals.STRUCTURED_NODE;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	public EList<org.univaq.hepsy.Process> getProcesses() {
		if (processes == null) {
			processes = new EObjectContainmentEList<org.univaq.hepsy.Process>(org.univaq.hepsy.Process.class, this,
					HepsyPackage.STRUCTURED_NODE__PROCESSES);
		}
		return processes;
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public NotificationChain eInverseRemove(InternalEObject otherEnd, int featureID, NotificationChain msgs) {
		switch (featureID) {
		case HepsyPackage.STRUCTURED_NODE__PROCESSES:
			return ((InternalEList<?>) getProcesses()).basicRemove(otherEnd, msgs);
		}
		return super.eInverseRemove(otherEnd, featureID, msgs);
	}

	/**
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	@Override
	public Object eGet(int featureID, boolean resolve, boolean coreType) {
		switch (featureID) {
		case HepsyPackage.STRUCTURED_NODE__PROCESSES:
			return getProcesses();
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
		case HepsyPackage.STRUCTURED_NODE__PROCESSES:
			getProcesses().clear();
			getProcesses().addAll((Collection<? extends org.univaq.hepsy.Process>) newValue);
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
		case HepsyPackage.STRUCTURED_NODE__PROCESSES:
			getProcesses().clear();
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
		case HepsyPackage.STRUCTURED_NODE__PROCESSES:
			return processes != null && !processes.isEmpty();
		}
		return super.eIsSet(featureID);
	}

} //StructuredNodeImpl
