package at.jku.se.eclipse.emf.ecore.sirius;

import java.util.HashMap;

import org.eclipse.sirius.business.api.session.Session;
import org.eclipse.sirius.business.api.session.SessionManagerListener;
import org.eclipse.sirius.viewpoint.description.Viewpoint;

public class SessionManager implements SessionManagerListener {

	HashMap<Session, Listener> listenerMap;

	public SessionManager() {
		listenerMap = new HashMap<Session, Listener>();
	}

	@Override
	public void notify(Session arg0, int arg1) {
		System.out.println("NOTIFY! : " + arg1);
		if(arg1 == 7 && arg0.getTransactionalEditingDomain() != null) { // opened
			Listener listener = new Listener(arg0);
			listenerMap.put(arg0, listener);
		}else if(arg1 == 9) {// closed
			Listener listener = listenerMap.get(arg0);
			listenerMap.remove(arg0);
			if (listener != null) {
				listener.serializeLog();
			}
		}
	}

	@Override
	public void notifyAddSession(Session arg0) {
		System.out.println("notifyAddSession: " + arg0);
//		Listener listener = new Listener(arg0);
//		listenerMap.put(arg0, listener);
	}

	@Override
	public void notifyRemoveSession(Session arg0) {
		System.out.println("notifyRemoveSession : " + arg0);
	}

	@Override
	public void viewpointDeselected(Viewpoint arg0) {
		System.out.println("viewpointDeselected : " + arg0);
		// TODO Auto-generated method stub
	}

	@Override
	public void viewpointSelected(Viewpoint arg0) {
		System.out.println("viewpointSelected: " + arg0);
		// TODO Auto-generated method stub
	}

}