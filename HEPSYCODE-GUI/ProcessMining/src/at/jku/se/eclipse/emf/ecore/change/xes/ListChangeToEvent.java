package at.jku.se.eclipse.emf.ecore.change.xes;

import org.deckfour.xes.factory.XFactory;
import org.deckfour.xes.model.impl.XEventImpl;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.util.EcoreUtil;

import at.jku.se.eclipse.emf.ecore.change.ListChange;

public class ListChangeToEvent extends XEventImpl {

	public ListChangeToEvent(ListChange l, XFactory factory) {
		String kind = l.getKind().getName();
		put("kind", kind);
		put("dataValues", l.getDataValues());
		put("index", l.getIndex());
		put("moveToIndex", l.getMoveToIndex());
		if (l.getReferenceValues() != null) {
			StringBuilder sb = new StringBuilder();
			sb.append("[");
			for (EObject e : l.getReferenceValues()) {
				if (e != null) {
					sb.append(EcoreUtil.getURI(e));
					sb.append(", ");
				}
			}
			if (sb.length() > 1) {
				sb.delete(sb.length() - 2, sb.length());
			}
			sb.append("]");
			put("referenceValues", sb.toString());
		}
	}

}
